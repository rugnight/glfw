//
//  main.cpp
//  glfw
//
//
#define GLFW_NO_GLU
#define GLFW_INCLUDE_GL3
#include <GL/glfw.h>
#include <OpenGL/glext.h>
#include <OpenGL/gl3ext.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <iostream>
#include <list>

#include "graphics/graphics.h"
#include "game/game.h"
#include "math/math.h"

using namespace rc;
using namespace rc::game;
using namespace rc::graphics;
using namespace rc::math;

using namespace std;

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

class IDrawable
{
public:
    virtual void draw() = 0;
};

class Font
{
    FT_Library  library_;
    FT_Face     face_;
    
public:
    Font()
    : library_(0)
    , face_(0)
    {
        
    }
    
    virtual ~Font()
    {
        release();
    }
    
    bool load(std::string file)
    {
        // freetypeの初期化
        if ( 0 < FT_Init_FreeType(&library_) ){
            return false;
        }
        
        // フォントフェイスをファイルからロード
        //  その他、メモリやwebから参照することも可能な様子
        u32 error = FT_New_Face(
                library_, 
                file.c_str(), 
                0,                      // 1ファイルに複数のフォントが含まれている場合に指定
                &face_);
        if ( error == FT_Err_Unknown_File_Format ) {
            // サポート外のフォントファイル
            return false;
        }
        else if ( error ) {
            // その他のエラー（ファイルが使用中とか、壊れているとか）
            return false;
        }

        // 文字サイズを設定
#if 0
        error = FT_Set_Char_Size(
                face,
                0,       // 文字幅、0を指定すると高さとおなじになる
                16*64,   // 文字高、
                300,     /* horizontal device resolution    */
                300 );   /* vertical device resolution      */
#else 
        // サイズ指定の簡易版関数
        error = FT_Set_Pixel_Sizes(
                face_,
                0,      // ピクセル幅
                16 );   // ピクセル高
#endif
        
        FT_GlyphSlot g = face_->glyph;
        int w = 0;
        int h = 0;
        
        for(int i = 32; i < 128; i++) {
            if(FT_Load_Char(face_, i, FT_LOAD_RENDER)) {
                fprintf(stderr, "Loading character %c failed!\n", i);
                continue;
            }
            
            w += g->bitmap.width;
            h = std::max(h, g->bitmap.rows);
            
            /* you might as well save this value as it is needed later on */
        }

        
        return true;
    }
    
    void release()
    {
        if (face_) {
            FT_Done_Face(face_);
        }
        if (library_) {
            FT_Done_FreeType(library_);
        }
    }

};


int main(int argc, const char * argv[])
{    
    Node root("root", NULL);
    Node child0("child0", &root);
    Node child1("child1", &root);
    Node child2("child2", &child0);
    Node child3("child3", &child2);
    //nodeTraversal<IDrawable>(&root, 0);
    
    glfwInit();

    // OpenGL Version 3.2 Core Profile を選択する
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
      
    glfwOpenWindow(500, 500, 8, 8, 8, 8, 24, 8, GLFW_WINDOW);
    
    // 開いたウィンドウに対する設定
    glfwSwapInterval(1);
    glfwSetWindowTitle("sample");
    
    //Font font;
    //font.load("/Users/rugnight/Developer/Workspace/glfw/Osaka.ttf");
    
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

    SpriteShader spriteShader;
    spriteShader.create();

    //Sprite sprite;
    //sprite.create("/Users/rugnight/Developer/Workspace/glfw/beauty.tga");

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
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#if 0
        // ------------------------------
        // Sprite
        // ------------------------------
        static Transform spriteTransform;
        spriteTransform.position(0, 0, 0.0f);
        spriteTransform.rotate(0.0f, 0.0f, spriteTransform.rotate().z+2.5f);
        sprite.setAnchor(Vector3(0.0f, 0.0f, 0.0f));
        Matrix4 transformMat = spriteTransform.matrix();
        
        spriteShader.begin();
        s32 matLoc = spriteShader.getUniformLocation("viewProjMat");
        spriteShader.setUniformMatrix4fv(matLoc, 1, false, &transformMat[0][0]);
        sprite.draw();
        spriteShader.end();
#endif
        
        // ------------------------------
        // Mesh
        // ------------------------------
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
        
        glfwSwapBuffers();
    }
    
    glfwTerminate();
    
    leak_check_dump("leak.txt");
    return 0;
}

