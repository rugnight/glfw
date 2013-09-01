//
//  main.cpp
//  glfw
//
//

#include "graphics_core.h"

#include <iostream>
#include <list>

#include "graphics/graphics.h"
#include "game/game.h"
#include "math/math.h"

using namespace rc;
using namespace rc::graphics;
using namespace rc::math;

using namespace std;

// -----------------------------------
// freetype2
#include <ft2build.h>
#include FT_FREETYPE_H

class SpriteFont : public Sprite
{
    static FT_Library  library_;
    static boolean initialize();
    static void terminate();

    FT_Face         face_; 
    FT_GlyphSlot    slot_;

    public:
        SpriteFont();
        virtual ~SpriteFont();

        void spriteWithFont(const char* fontFilePath);
};

FT_Library  SpriteFont::library_ = NULL;

SpriteFont::SpriteFont()
    : face_(0)
    , slot_(0)
{
}

SpriteFont::~SpriteFont()
{
}

boolean SpriteFont::initialize()
{
    u32 error = FT_Init_FreeType(&library_);
    if ( error ) {
        return false;
    }
    return true;
}

void SpriteFont::terminate()
{
}

void SpriteFont::spriteWithFont(const char* fontFilePath)
{
    if ( NULL == SpriteFont::library_ ) {
        boolean success = initialize();
        if ( !success ) {
            return ;
        }
    }

    u32 error = FT_New_Face(SpriteFont::library_, fontFilePath, 0, &face_);
    if ( error == FT_Err_Unknown_File_Format ) {
        return ;

    } else if ( error ) {
        return ;

    }
    
    FT_Set_Pixel_Sizes(face_, 48, 48);
    
    FT_Load_Char(face_, u'明', 0);
    FT_Render_Glyph(face_->glyph, FT_RENDER_MODE_NORMAL);
    FT_Bitmap *bm = &face_->glyph->bitmap;
    
    u32 width  = bm->width;
    u32 height = bm->rows;
    u32 pitch = 1;
    GLuint * img = new GLuint[width * height];
    memset( img, 0, sizeof(GLuint) * width * height);
    
    int c ;
    for (int row = 0; row < bm->rows; row ++) {
        for (int col = 0; col < bm->pitch; col  ++) {
            c = bm->buffer[bm->pitch * (bm->rows-row) + col];
            img[row*width+col] = 0x00ffffff | (c << 24);
        }
    }

    // テクスチャを生成して書き込む
    Texture texture = Texture(new TextureBase(width, height, RGBA));
    texture->writeImage(0, 0, width, height, RGBA, img);
    texture->bind();
        texture->setWrapModeS(WRAP_CLAMP);
        texture->setWrapModeT(WRAP_CLAMP);
        texture->setMagFilterMode(MIPMAP_LINEAR);
        texture->setMinFilterMode(MIPMAP_LINEAR);
    texture->unbind();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    delete []img;

    this->create(texture);
}

// freetype2
// -----------------------------------

class Node
{
    private:
        Node() { Node("", NULL); }
    public:
        Node(std::string name, Node *parent)
        : name_(name)
        , parent_(parent)
        {
            if (parent_) {
                parent_->addChild(this);
            }
        }
    
        virtual ~Node() {}

        const std::string& name() { return name_; }

        Node* parent() { return parent_; }
        void setParent(Node *node) { parent_ = node; }

        std::list<Node*>* childlen() { return &childlen_; }
        void addChild(Node *child) { child->setParent(this); childlen_.push_back(child); }

    private:
        std::string name_;

        Node*   parent_;
        std::list<Node*> childlen_;

        Transform   transform_;
};

class Scene : public Node
{
public:
    Scene(std::string name)
    : Node(name, NULL)
    {
    
    };
    
    virtual ~Scene() {}
    
private:
};

template<class T>
void nodeTraversal(T *node, u32 depth)
{
    if (NULL == node) {
        return ;
    }
    
    for( int i = 0; i < depth; ++i ) { printf("-"); }
    printf("%s\n", node->name().c_str());
    
    for ( auto it = node->childlen()->begin(); it != node->childlen()->end(); ++it ) {
        nodeTraversal<T>(*it, ++depth);

    }
}

static Texture fontTex = NULL;

class IDrawable
{
public:
    virtual void draw() = 0;
};

int main(int argc, const char * argv[])
{    
    //Node root("root", NULL);
    //Node child0("child0", &root);
    //Node child1("child1", &root);
    //Node child2("child2", &child0);
    //Node child3("child3", &child2);
    //nodeTraversal<IDrawable>(&root, 0);
    
    Render::self().initialize(500, 500);
    
    // バーテックスシェーダのソースプログラム
    static const GLchar vsrc0[] =
        "#version 330 core\n"
        "layout(location = 0) in vec3 pv;\n"
        "layout(location = 1) in vec3 normal;\n"
        "layout(location = 2) in vec2 vertexUV;\n"
        "out vec2 uv;\n"
        "uniform mat4 viewProjMat;\n"
        "void main(){\n"
        "    gl_Position = viewProjMat * vec4(pv, 1);\n"
        "    uv = vertexUV;\n"
        "}\n";
    
    // フラグメントシェーダのソースプログラム
    static const GLchar fsrc0[] =
        "#version 330 core\n"
        "in vec2 uv;\n"
        "out vec4 color;\n"
        "uniform sampler2D sampler;\n"
        "void main(){\n"
        "   color = texture( sampler, uv ).rgba + vec4(0.1, 0.1, 0.1, 0.1);\n"
        //"   color = vec4(1.0, 1.0, 1.0, 0.0);\n"
        "}\n";

    // プログラムオブジェクトの作成
    ShaderProgram shader;
    shader.create(vsrc0, fsrc0);

    SpriteFont fontSprite;
    fontSprite.spriteWithFont("/Users/rugnight/Developer/Workspace/glfw/Osaka.ttf");

    Sprite sprite;
    sprite.create("/Users/rugnight/Developer/Workspace/glfw/beauty.tga");
    //sprite.create(fontTex);
    
    Model mesh;
    mesh.createFromFile("/Users/rugnight/Developer/Workspace/glfw/mikuA.obj");

    // Zテストの設定
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    while (glfwGetWindowParam(GLFW_OPENED)) {
        
        static f32 camX = 0.0f;
        static f32 camY = 0.0f;
        static f32 camZ = 100.0f;
        static f32 posX = 0.0f;
        static f32 posY = 0.0f;
        static f32 rotX = 0.0f;
        static f32 rotY = 0.0f;
        if ( glfwGetKey('W') ) { rotX += 1.1f; }
        if ( glfwGetKey('S') ) { rotX -= 1.1f; }
        if ( glfwGetKey('A') ) { rotY += 1.1f; }
        if ( glfwGetKey('D') ) { rotY -= 1.1f; }
        
        glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#if 1
        // ------------------------------
        // Sprite
        // ------------------------------
        static Transform spriteTransform;
        spriteTransform.position(0, 0, 0.0f);
        spriteTransform.rotate(0.0f, 0.0f, spriteTransform.rotate().z+2.5f);
        sprite.setAnchor(Vector3(0.0f, 0.0f, 0.0f));
        Matrix4 transformMat = spriteTransform.matrix();
        Vector2 screen = Vector2(500, 500);
        
        Render::self().spriteShader().begin();
        
        Render::self().spriteShader().setAffine(spriteTransform.matrix());
        Render::self().spriteShader().setScreen(screen);
        sprite.draw();

        Render::self().spriteShader().setAffine(Matrix4(1.0f));
        Render::self().spriteShader().setScreen(screen);
        fontSprite.draw();
        
        Render::self().spriteShader().end();
        
#endif
        
        // ------------------------------
        // Mesh
        // ------------------------------
#if 0
        Transform transform;
        transform.position(Vector3(posX, posY, 0.0f));
        transform.rotate(Vector3(rotX, rotY, 0.0f));
        transform.scale(Vector3(1.0f, 1.0f, 1.0f));
        
        Matrix4 viewMat = glm::lookAt(glm::vec3(camX, camY, camZ),
                                      glm::vec3(0.0f, 0.0f, 0.0f),
                                      glm::vec3(0.0f, 1.0f, 0.0f));
        Matrix4 projMat = glm::perspective(30.0f, 4.0f/3.0f, 0.1f, 1000.0f);
        Matrix4 wvpMat = projMat * viewMat * transform.matrix();
        
        shader.begin();
        s32 vpmLoc = shader.getUniformLocation("viewProjMat");
        shader.setUniformMatrix4fv(vpmLoc, 1, false, &wvpMat[0][0]);
        mesh.draw();
        shader.end();
#endif
    
        glfwSwapBuffers();
    }

    Render::self().terminate();
    glfwTerminate();
    
    //leak_check_dump("leak.txt");
    return 0;
}

