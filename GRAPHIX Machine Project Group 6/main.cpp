#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Model Class
class Model3D
{
public:
    std::vector<float> x, y, z;
    std::vector<float> rotX, rotY, rotZ, theta;
    std::vector<float> scaleX, scaleY, scaleZ;

    glm::mat4 identity_matrix = glm::mat4(1.0f);

    glm::vec3 subPos;
    float pRotX, pRotY, pRotZ, pThetaX, pThetaY;
    float pScaleX, pScaleY, pScaleZ;

    void Draw(GLuint shaderProgram, GLuint VAO, std::vector<GLfloat> fullVertexData, GLuint texture, int i) {

        unsigned int transformationLoc = glGetUniformLocation(shaderProgram, "transform");
        GLuint tex0Address = glGetUniformLocation(shaderProgram, "tex0");
        

        std::vector<glm::mat4> transformation_matrix;

        transformation_matrix.push_back(glm::translate(identity_matrix, glm::vec3(x[i], y[i], z[i])));
        transformation_matrix[0] = glm::rotate(transformation_matrix[0], glm::radians(theta[i]), glm::normalize(glm::vec3(rotX[i], rotY[i], rotZ[i])));
        transformation_matrix[0] = glm::scale(transformation_matrix[0], glm::vec3(scaleX[i], scaleY[i], scaleZ[i]));

        glBindVertexArray(VAO);
        glUniformMatrix4fv(transformationLoc, 1, GL_FALSE, glm::value_ptr(transformation_matrix[0]));

        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(tex0Address, 0);

        glDrawArrays(GL_TRIANGLES, 0, fullVertexData.size() / 8);
    }

    void DrawPlayer(GLuint shaderProgram, GLuint VAO, std::vector<GLfloat> fullVertexData, GLuint texture) {
        unsigned int transformationLoc = glGetUniformLocation(shaderProgram, "transform");
        GLuint tex0Address = glGetUniformLocation(shaderProgram, "tex0");


        std::vector<glm::mat4> transformation_matrix;

        transformation_matrix.push_back(glm::translate(identity_matrix, subPos));
        transformation_matrix[0] = glm::rotate(transformation_matrix[0], glm::radians(pThetaX), glm::normalize(glm::vec3(1, 0, 0)));
        transformation_matrix[0] = glm::rotate(transformation_matrix[0], glm::radians(pThetaY), glm::normalize(glm::vec3(0, 0, 1)));
        transformation_matrix[0] = glm::scale(transformation_matrix[0], glm::vec3(pScaleX, pScaleY, pScaleZ));

        glBindVertexArray(VAO);
        glUniformMatrix4fv(transformationLoc, 1, GL_FALSE, glm::value_ptr(transformation_matrix[0]));

        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(tex0Address, 0);

        glDrawArrays(GL_TRIANGLES, 0, fullVertexData.size() / 8);
    }

    void insertValues() {
        // shark 2
        x.push_back(470.0f);
        y.push_back(-180.0f);
        z.push_back(-30.0f);
        rotX.push_back(1.0f);
        rotY.push_back(0.0f);
        rotZ.push_back(0.0f);
        theta.push_back(270.0f);
        scaleX.push_back(0.3f);
        scaleY.push_back(0.3f);
        scaleZ.push_back(0.3f);

        
        // squid
        x.push_back(35.0f);
        y.push_back(-160.0f);
        z.push_back(80.0f);
        rotX.push_back(0.0f);
        rotY.push_back(1.0f);
        rotZ.push_back(0.0f);
        theta.push_back(90.0f);
        scaleX.push_back(0.25f);
        scaleY.push_back(0.25f);
        scaleZ.push_back(0.25f);

        // shark
        x.push_back(280.0f);
        y.push_back(-240.0f);
        z.push_back(240.0f);
        rotX.push_back(1.0f);
        rotY.push_back(0.0f);
        rotZ.push_back(0.0f);
        theta.push_back(270.0f);
        scaleX.push_back(0.05f);
        scaleY.push_back(0.05f);
        scaleZ.push_back(0.05f);

        // sea urchin
        x.push_back(10.0f);
        y.push_back(-300.0f);
        z.push_back(-35.0f);
        rotX.push_back(1.0f);
        rotY.push_back(0.0f);
        rotZ.push_back(0.0f);
        theta.push_back(270.0f);
        scaleX.push_back(0.70f);
        scaleY.push_back(0.70f);
        scaleZ.push_back(0.70f);

        // coral
        x.push_back(20.0f);
        y.push_back(-300.0f);
        z.push_back(-25.0f);
        rotX.push_back(1.0f);
        rotY.push_back(0.0f);
        rotZ.push_back(0.0f);
        theta.push_back(270.0f);
        scaleX.push_back(0.75f);
        scaleY.push_back(0.75f);
        scaleZ.push_back(0.75f);

        // table coral
        x.push_back(90.0f);
        y.push_back(-300.0f);
        z.push_back(75.0f);
        rotX.push_back(1.0f);
        rotY.push_back(0.0f);
        rotZ.push_back(0.0f);
        theta.push_back(270.0f);
        scaleX.push_back(0.75f);
        scaleY.push_back(0.75f);
        scaleZ.push_back(0.75f);

        // alligator
        x.push_back(110.0f);
        y.push_back(-30.0f);
        z.push_back(-80.0f);
        rotX.push_back(1.0f);
        rotY.push_back(0.0f);
        rotZ.push_back(0.0f);
        theta.push_back(270.0f);
        scaleX.push_back(0.75f);
        scaleY.push_back(0.75f);
        scaleZ.push_back(0.75f);

        subPos.x = subPos.y = subPos.z = -0.1f;
        pRotX = pRotY = pRotZ = 0.f;
        pRotX = 1.0f;
        pThetaX = 270.f;
        pThetaY = 0.f;
        pScaleX = pScaleY = pScaleZ = 0.001f;
    }
};

class Lighting
{
public:
    glm::vec3 lightDir;
    glm::vec3 lightColor;

    float ambientStr;
    glm::vec3 ambientColor;

    float specStr;
    float specPhong;

    glm::vec3 lightPos;

    glm::vec3 subLightColor;

    float subAmbientStr;
    glm::vec3 subAmbientColor;

    float subSpecStr;
    float subSpecPhong;

    void GenerateLight(GLuint shaderProgram, glm::vec3 cameraPos) {
        unsigned lightDirLoc = glGetUniformLocation(shaderProgram, "lightDirection");
        glUniform3fv(lightDirLoc, 1, glm::value_ptr(lightDir));

        unsigned lightColorLoc = glGetUniformLocation(shaderProgram, "lightColor");
        glUniform3fv(lightColorLoc, 1, glm::value_ptr(lightColor));

        unsigned int ambientStrLoc = glGetUniformLocation(shaderProgram, "ambientStr");
        glUniform1f(ambientStrLoc, ambientStr);

        unsigned int ambientColorLoc = glGetUniformLocation(shaderProgram, "ambientColor");
        glUniform3fv(ambientColorLoc, 1, glm::value_ptr(ambientColor));

        unsigned int cameraPosLoc = glGetUniformLocation(shaderProgram, "cameraPos");
        glUniform3fv(cameraPosLoc, 1, glm::value_ptr(cameraPos));

        unsigned int specStrLoc = glGetUniformLocation(shaderProgram, "specStr");
        glUniform1f(specStrLoc, specStr);

        unsigned int specPhongLoc = glGetUniformLocation(shaderProgram, "specPhong");
        glUniform1f(specPhongLoc, specPhong);

        unsigned int pointLightPosLoc = glGetUniformLocation(shaderProgram, "pointLightPos");
        glUniform3fv(pointLightPosLoc, 1, glm::value_ptr(lightPos));

        unsigned int pointLightColorLoc = glGetUniformLocation(shaderProgram, "pointLightColor");
        glUniform3fv(pointLightColorLoc, 1, glm::value_ptr(subLightColor));

        unsigned int pointAmbientStrLoc = glGetUniformLocation(shaderProgram, "pointAmbientStr");
        glUniform1f(pointAmbientStrLoc, subAmbientStr);

        unsigned int pointAmbientColorLoc = glGetUniformLocation(shaderProgram, "pointAmbientColor");
        glUniform3fv(pointAmbientColorLoc, 1, glm::value_ptr(subAmbientColor));

        unsigned int pointSpecStrLoc = glGetUniformLocation(shaderProgram, "pointSpecStr");
        glUniform1f(pointSpecStrLoc, subSpecStr);

        unsigned int pointSpecPhongLoc = glGetUniformLocation(shaderProgram, "pointSpecPhong");
        glUniform1f(pointSpecPhongLoc, subSpecPhong);

    }
};

class Shaders {
public:

    GLuint GenerateShaders(std::string filename) {
        std::fstream vertSrc("Shaders/" + filename + ".vert");
        std::stringstream vertBuff;
        vertBuff << vertSrc.rdbuf();
        std::string vertString = vertBuff.str();
        const char* v = vertString.c_str();

        std::fstream fragSrc("Shaders/" + filename + ".frag");
        std::stringstream fragBuff;
        fragBuff << fragSrc.rdbuf();
        std::string fragString = fragBuff.str();
        const char* f = fragString.c_str();

        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &v, NULL);
        glCompileShader(vertexShader);

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &f, NULL);
        glCompileShader(fragmentShader);

        GLuint shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);

        glLinkProgram(shaderProgram);

        return shaderProgram;
    }
    
};

class Textures {
public:

    GLuint GenerateTexture(std::string filename, bool isJpg) {
        GLuint texture;
        if (isJpg) {
            int img_width, img_height, color_channels;
            std::string file = "3D/" + filename + ".jpg";
            unsigned char* tex_bytes = stbi_load(file.data(), &img_width, &img_height, &color_channels, 0);

            glGenTextures(1, &texture);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width, img_height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_bytes);

            glGenerateMipmap(GL_TEXTURE_2D);
            stbi_image_free(tex_bytes);
        }
        else {
            int img_width, img_height, color_channels;
            std::string file = "3D/" + filename + ".png";
            unsigned char* tex_bytes = stbi_load(file.data(), &img_width, &img_height, &color_channels, 0);

            glGenTextures(1, &texture);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_width, img_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex_bytes);

            glGenerateMipmap(GL_TEXTURE_2D);
            stbi_image_free(tex_bytes);
        }
        

        return texture;
    }
    
};

Model3D model;
Lighting lighting;
Shaders shaders;
Textures textures;
float x_mod = 0.f;
float y_mod = 0.f;
float z_mod = 0.f;
float lastX = 300, lastY = 300;
float pitch = 0.0f, yaw = 0.0f;

glm::vec3 F, R, U;
glm::vec3 cameraPos;
float subx = cameraPos.x + F.x * 4;
float suby = cameraPos.y + F.y * 4;
float subz = cameraPos.z + F.z * 4;

//instantiate direction vector
glm::vec3 direction;

float pTheta = 0.f;

bool first = true;
bool isThirdPerson = true;

float delayTime = 0;

const float cameraSpeed = 0.5f;

void Key_Callback(GLFWwindow* window, int key, int scanCode, int action, int mods) {

    if (key == GLFW_KEY_A) {
        model.pThetaY += 3.f;
    }

    if (key == GLFW_KEY_D) {
        model.pThetaY -= 3.f;
    }

    if (key == GLFW_KEY_W) {
        model.subPos.x -= (1.0f * sinf(glm::radians(model.pThetaY)));
        model.subPos.z -= (1.0f * cosf(glm::radians(model.pThetaY)));

        cameraPos.x -= (1.0f * sinf(glm::radians(model.pThetaY)));
        cameraPos.z -= (1.0f * cosf(glm::radians(model.pThetaY)));
    }

    if (key == GLFW_KEY_S) {
        model.subPos.x += (1.0f * sinf(glm::radians(model.pThetaY)));
        model.subPos.z += (1.0f * cosf(glm::radians(model.pThetaY)));

        cameraPos.x += (1.0f * sinf(glm::radians(model.pThetaY)));
        cameraPos.z += (1.0f * cosf(glm::radians(model.pThetaY)));
    }

    if (key == GLFW_KEY_Q && model.subPos.y < 0.1f) {
        model.subPos.y += 0.25f;
        cameraPos.y += 0.25f;
    }

    if (key == GLFW_KEY_E) {
        model.subPos.y -= 0.25f;
        cameraPos.y -= 0.25f;
    }

    if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
        if ((clock() / CLOCKS_PER_SEC) > delayTime) {
            if (isThirdPerson) {
                isThirdPerson = false;
                cameraPos.y = cameraPos.y - 3.0f;
            }
            else {
                isThirdPerson = true;
                cameraPos.y = cameraPos.y + 3.0f;
            }
                

            delayTime = clock() / CLOCKS_PER_SEC + 3;   // 3 secs delay
        }
        
    }
}

void Mouse_Callback(GLFWwindow* window, double xpos, double ypos) {
    if (isThirdPerson) {
        //if mouse enters the window, set last position to current position
        if (first)
        {
            lastX = xpos;
            lastY = ypos;
            first = false;
        }

        //get the offset of the x and y
        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top

        lastX = xpos;
        lastY = ypos;

        //apply sensitivity to offset
        const float sensitivity = 0.1f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;
        yaw += xoffset;
        pitch += yoffset;

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        //get the X, Y, and Z values of the direction using euler angles
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        //Normalize direction vector and store to F
        F = glm::normalize(direction);
    }
};

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    float screenWidth = 1200.f;
    float screenHeight = 1200.f;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(screenWidth, screenHeight, "Jerez - Llorca - Tee: GRAPHIX Machine Project Group 6", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    std::string path[9] = { "3D/shark2.obj", "3D/squid.obj", "3D/shark.obj", "3D/seaurchin.obj", "3D/coral.obj", "3D/tablecoral.obj", "3D/alligatorgar.obj", "3D/submarine.obj", "3D/sonar.obj"};
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warning, error;

    tinyobj::attrib_t attributes;

    GLfloat UV[]{
        0.f, 1.f,
        0.f, 0.f,
        1.f, 1.f,
        1.f, 0.f,
        1.f, 1.f,
        1.f, 0.f,
        0.f, 1.f,
        0.f, 0.f
    };

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    //Initialize GLAD
    gladLoadGL();

    stbi_set_flip_vertically_on_load(true);

    GLuint texture1 = textures.GenerateTexture("shark", true);
    GLuint texture2 = textures.GenerateTexture("sq_texture", true);
    GLuint texture3 = textures.GenerateTexture("whaleshark", true);
    GLuint texture4 = textures.GenerateTexture("seaurchin", true);
    GLuint texture5 = textures.GenerateTexture("coral", true);
    GLuint texture6 = textures.GenerateTexture("tablecoral", true);
    GLuint texture7 = textures.GenerateTexture("alligator", true);
    GLuint texture8 = textures.GenerateTexture("submarine", true);


    glEnable(GL_DEPTH_TEST);

    glfwSetKeyCallback(window, Key_Callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, Mouse_Callback);

    GLuint shaderProgram = shaders.GenerateShaders("models");

    GLuint playerShaderProgram = shaders.GenerateShaders("player");

    /*
      7--------6
     /|       /|
    4--------5 |
    | |      | |
    | 3------|-2
    |/       |/
    0--------1
    */
    //Vertices for the cube
    float skyboxVertices[]{
        -1.f, -1.f, 1.f, //0
        1.f, -1.f, 1.f,  //1
        1.f, -1.f, -1.f, //2
        -1.f, -1.f, -1.f,//3
        -1.f, 1.f, 1.f,  //4
        1.f, 1.f, 1.f,   //5
        1.f, 1.f, -1.f,  //6
        -1.f, 1.f, -1.f  //7
    };

    //Skybox Indices
    unsigned int skyboxIndices[]{
        1,2,6,
        6,5,1,

        0,4,7,
        7,3,0,

        4,5,6,
        6,7,4,

        0,3,2,
        2,1,0,

        0,1,5,
        5,4,0,

        3,7,6,
        6,2,3
    };

    unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glGenBuffers(1, &skyboxEBO);

    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GL_INT) * 36, &skyboxIndices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);

    std::string facesSkybox[]{
        "Skybox/is_right.png", //Right
        "Skybox/is_left.png", //Left
        "Skybox/is_up.png", //Up
        "Skybox/is_down.png", //Down
        "Skybox/is_front.png", //Front
        "Skybox/is_back.png", //Back
    };

    unsigned int skyboxTex;

    glGenTextures(1, &skyboxTex);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTex);

    //Prevents pixelating
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //Prevents tiling
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    for (unsigned int i = 0; i < 6; i++) {

        int w, h, skyCChanel;
        stbi_set_flip_vertically_on_load(false);

        unsigned char* data = stbi_load(facesSkybox[i].c_str(),
            &w,
            &h,
            &skyCChanel,
            0);
        if (data) {
            glTexImage2D(
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0,
                GL_RGBA,
                w,
                h,
                0,
                GL_RGBA,
                GL_UNSIGNED_BYTE,
                data
            );
        }

        stbi_image_free(data);
    }
    stbi_set_flip_vertically_on_load(true);

    GLuint skybox_shaderProg = shaders.GenerateShaders("skybox");
    
    std::vector<GLfloat> fullVertexData[9];

    for (int j = 0; j < 9; j++) {
        // LOADING OBJECTS
        bool success = tinyobj::LoadObj(
            &attributes,
            &shapes,
            &materials,
            &warning,
            &error,
            path[j].c_str()
        );

        
        for (int i = 0; i < shapes[0].mesh.indices.size(); i++) {
            tinyobj::index_t vData = shapes[0].mesh.indices[i];

            int vertexIndex = vData.vertex_index * 3;
            int normalIndex = vData.normal_index * 3;
            int uvIndex = vData.texcoord_index * 2;

            fullVertexData[j].push_back(attributes.vertices[(vData.vertex_index * 3)]);
            fullVertexData[j].push_back(attributes.vertices[(vData.vertex_index * 3) + 1]);
            fullVertexData[j].push_back(attributes.vertices[(vData.vertex_index * 3) + 2]);
            fullVertexData[j].push_back(attributes.normals[(vData.normal_index * 3)]);
            fullVertexData[j].push_back(attributes.normals[(vData.normal_index * 3) + 1]);
            fullVertexData[j].push_back(attributes.normals[(vData.normal_index * 3) + 2]);
            fullVertexData[j].push_back(attributes.texcoords[(vData.texcoord_index * 2)]);
            fullVertexData[j].push_back(attributes.texcoords[(vData.texcoord_index * 2) + 1]);
        }
    }
    


    /*  MODELS VAO AND VBO */
    GLuint VAO1, VBO1, VAO2, VBO2, VAO3, VBO3, VAO4, VBO4, VAO5, VBO5, VAO6, VBO6, VAO7, VBO7;
    glGenVertexArrays(1, &VAO1);
    glGenBuffers(1, &VBO1);
    glGenVertexArrays(1, &VAO2);
    glGenBuffers(1, &VBO2);
    glGenVertexArrays(1, &VAO3);
    glGenBuffers(1, &VBO3);
    glGenVertexArrays(1, &VAO4);
    glGenBuffers(1, &VBO4);
    glGenVertexArrays(1, &VAO5);
    glGenBuffers(1, &VBO5);
    glGenVertexArrays(1, &VAO6);
    glGenBuffers(1, &VBO6);
    glGenVertexArrays(1, &VAO7);
    glGenBuffers(1, &VBO7);

    // OBJ1
    glBindVertexArray(VAO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(GL_FLOAT) * fullVertexData[0].size(),
        fullVertexData[0].data(),
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)0
    );

    GLintptr normPtr = 3 * sizeof(GLfloat);
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)normPtr
    );

    GLintptr uvPtr = 6 * sizeof(GLfloat);
    glVertexAttribPointer(
        2,
        2,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)uvPtr
    );

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // OBJ2
    glBindVertexArray(VAO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(GL_FLOAT) * fullVertexData[1].size(),
        fullVertexData[1].data(),
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)0
    );

    normPtr = 3 * sizeof(GLfloat);
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)normPtr
    );

    uvPtr = 6 * sizeof(GLfloat);
    glVertexAttribPointer(
        2,
        2,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)uvPtr
    );

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // OBJ3
    glBindVertexArray(VAO3);
    glBindBuffer(GL_ARRAY_BUFFER, VBO3);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(GL_FLOAT)* fullVertexData[2].size(),
        fullVertexData[2].data(),
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)0
    );

    normPtr = 3 * sizeof(GLfloat);
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)normPtr
    );

    uvPtr = 6 * sizeof(GLfloat);
    glVertexAttribPointer(
        2,
        2,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)uvPtr
    );

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // OBJ4
    glBindVertexArray(VAO4);
    glBindBuffer(GL_ARRAY_BUFFER, VBO4);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(GL_FLOAT)* fullVertexData[3].size(),
        fullVertexData[3].data(),
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)0
    );

    normPtr = 3 * sizeof(GLfloat);
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)normPtr
    );

    uvPtr = 6 * sizeof(GLfloat);
    glVertexAttribPointer(
        2,
        2,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)uvPtr
    );

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // OBJ5
    glBindVertexArray(VAO5);
    glBindBuffer(GL_ARRAY_BUFFER, VBO5);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(GL_FLOAT)* fullVertexData[4].size(),
        fullVertexData[4].data(),
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)0
    );

    normPtr = 3 * sizeof(GLfloat);
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)normPtr
    );

    uvPtr = 6 * sizeof(GLfloat);
    glVertexAttribPointer(
        2,
        2,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)uvPtr
    );

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // OBJ6
    glBindVertexArray(VAO6);
    glBindBuffer(GL_ARRAY_BUFFER, VBO6);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(GL_FLOAT)* fullVertexData[5].size(),
        fullVertexData[5].data(),
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)0
    );

    normPtr = 3 * sizeof(GLfloat);
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)normPtr
    );

    uvPtr = 6 * sizeof(GLfloat);
    glVertexAttribPointer(
        2,
        2,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)uvPtr
    );

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // OBJ6
    glBindVertexArray(VAO7);
    glBindBuffer(GL_ARRAY_BUFFER, VBO7);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(GL_FLOAT)* fullVertexData[6].size(),
        fullVertexData[6].data(),
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)0
    );

    normPtr = 3 * sizeof(GLfloat);
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)normPtr
    );

    uvPtr = 6 * sizeof(GLfloat);
    glVertexAttribPointer(
        2,
        2,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)uvPtr
    );

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    GLuint SVAO, SVBO;
    glGenVertexArrays(1, &SVAO);
    glGenBuffers(1, &SVBO);

    // Sonar
    glBindVertexArray(SVAO);
    glBindBuffer(GL_ARRAY_BUFFER, SVBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(GL_FLOAT)* fullVertexData[8].size(),
        fullVertexData[8].data(),
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)0
    );

    normPtr = 3 * sizeof(GLfloat);
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)normPtr
    );

    uvPtr = 6 * sizeof(GLfloat);
    glVertexAttribPointer(
        2,
        2,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)uvPtr
    );

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    /*  PLAYER VAO AND VBO */
    GLuint PVAO, PVBO;
    glGenVertexArrays(1, &PVAO);
    glGenBuffers(1, &PVBO);

    glBindVertexArray(PVAO);
    glBindBuffer(GL_ARRAY_BUFFER, PVBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(GL_FLOAT) * fullVertexData[7].size(),
        fullVertexData[7].data(),
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)0
    );

    normPtr = 3 * sizeof(GLfloat);
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)normPtr
    );

    uvPtr = 6 * sizeof(GLfloat);
    glVertexAttribPointer(
        2,
        2,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)uvPtr
    );

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    model.insertValues();

    // PAPALITAN SA DULO
    glm::mat4 projection_matrix = glm::perspective(glm::radians(60.f), screenHeight / screenWidth, 0.1f, 500.f);

    lighting.lightDir = glm::vec3(0, -1, 0);
    lighting.lightColor = glm::vec3(1, 1, 1);
    lighting.ambientColor = glm::vec3(1, 1, 1);
    lighting.ambientStr = 0.01f;
    lighting.specStr = 0.1f;
    lighting.specPhong = 16.0f;
    
    lighting.lightPos = cameraPos;
    lighting.subLightColor = glm::vec3(1, 1, 1);
    lighting.subAmbientColor = glm::vec3(1, 1, 1);
    lighting.subAmbientStr = 0.1f;
    lighting.subSpecStr = 0.1f;
    lighting.subSpecPhong = 16.0f;

    cameraPos = glm::vec3(0.f, 3.f, 0.f);
    glm::mat4 cameraPosMatrix = glm::translate(glm::mat4(1.0f), cameraPos * -1.f);

    glm::vec3 worldUp = glm::vec3(0, 1.0f, 0);
    glm::vec3 cameraCenter = glm::vec3(0.1f, 0.1f, 0.1f);
    F = glm::vec3(cameraCenter - cameraPos);
    F = glm::normalize(F);

    direction = glm::vec3(0.0f, 0.0f, 0.0f);
    /* Loop until the user closes the window */
     while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 viewMatrix;

        //Construct the Camera Orientation Matrix
        glm::mat4 cameraOrientation = glm::mat4(1.f);

        lighting.lightPos = cameraPos;

        if (isThirdPerson) {

            /*cameraPos = glm::vec3(0, 0, 10.f);*/
            cameraPosMatrix = glm::translate(glm::mat4(1.0f), cameraPos * -1.f);
            R = glm::normalize(glm::cross(F, worldUp));
            U = glm::normalize(glm::cross(R, F));

            cameraOrientation[0][0] = R.x;
            cameraOrientation[1][0] = R.y;
            cameraOrientation[2][0] = R.z;

            cameraOrientation[0][1] = U.x;
            cameraOrientation[1][1] = U.y;
            cameraOrientation[2][1] = U.z;

            cameraOrientation[0][2] = -F.x;
            cameraOrientation[1][2] = -F.y;
            cameraOrientation[2][2] = -F.z;

            viewMatrix = cameraOrientation * cameraPosMatrix;

            glUseProgram(playerShaderProgram);

            lighting.GenerateLight(playerShaderProgram, cameraPos);

            unsigned int pProjectionLoc = glGetUniformLocation(playerShaderProgram, "projection");
            glUniformMatrix4fv(pProjectionLoc, 1, GL_FALSE, glm::value_ptr(projection_matrix));

            unsigned int pViewLoc = glGetUniformLocation(playerShaderProgram, "view");
            glUniformMatrix4fv(pViewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

            model.DrawPlayer(playerShaderProgram, PVAO, fullVertexData[7], texture8);

        }
        else {
            cameraPosMatrix = glm::translate(glm::mat4(1.0f), cameraPos * -1.f);

            //F = glm::vec3(model.subPos.x - (1.0f * sinf(glm::radians(model.pThetaY))), model.subPos.y, model.subPos.z - (1.0f * cosf(glm::radians(model.pThetaY))));
            F = glm::vec3(model.subPos.x, model.subPos.y, model.subPos.z);
            F = glm::normalize(F);
            R = glm::normalize(glm::cross(F, worldUp));
            U = glm::normalize(glm::cross(R, F));

            cameraOrientation[0][0] = R.x;
            cameraOrientation[1][0] = R.y;
            cameraOrientation[2][0] = R.z;

            cameraOrientation[0][1] = U.x;
            cameraOrientation[1][1] = U.y;
            cameraOrientation[2][1] = U.z;

            cameraOrientation[0][2] = -F.x;
            cameraOrientation[1][2] = -F.y;
            cameraOrientation[2][2] = -F.z;

            viewMatrix = cameraOrientation * cameraPosMatrix;
        }
        

        glDepthMask(GL_FALSE);
        glDepthFunc(GL_LEQUAL);

        glUseProgram(skybox_shaderProg);

        glm::mat4 sky_view = glm::mat4(1.f);
        //To remove the position of the camera
        //Rotation camera for our skybox
        sky_view = glm::mat4(glm::mat3(viewMatrix));

        unsigned int sky_projectionLoc = glGetUniformLocation(skybox_shaderProg, "projection");
        glUniformMatrix4fv(sky_projectionLoc,
            1,
            GL_FALSE,
            glm::value_ptr(projection_matrix));

        unsigned int sky_viewLoc = glGetUniformLocation(skybox_shaderProg, "view");
        glUniformMatrix4fv(sky_viewLoc,
            1,
            GL_FALSE,
            glm::value_ptr(sky_view));

        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTex);

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LESS);

        glUseProgram(shaderProgram);

        lighting.GenerateLight(shaderProgram, cameraPos);

        unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection_matrix));
        
        unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

        model.Draw(shaderProgram, VAO1, fullVertexData[0], texture1, 0);
        model.Draw(shaderProgram, VAO2, fullVertexData[1], texture2, 1);
        model.Draw(shaderProgram, VAO3, fullVertexData[2], texture3, 2);
        model.Draw(shaderProgram, VAO4, fullVertexData[3], texture4, 3);
        model.Draw(shaderProgram, VAO5, fullVertexData[4], texture5, 4);
        model.Draw(shaderProgram, VAO6, fullVertexData[5], texture6, 5);
        model.Draw(shaderProgram, VAO7, fullVertexData[6], texture7, 6);

        

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO1);
    glDeleteBuffers(1, &VBO1);
    glDeleteVertexArrays(1, &VAO2);
    glDeleteBuffers(1, &VBO2);
    glDeleteVertexArrays(1, &VAO3);
    glDeleteBuffers(1, &VBO3);
    glDeleteVertexArrays(1, &VAO4);
    glDeleteBuffers(1, &VBO4);
    glDeleteVertexArrays(1, &VAO5);
    glDeleteBuffers(1, &VBO5);
    glDeleteVertexArrays(1, &VAO6);
    glDeleteBuffers(1, &VBO6);
    glDeleteVertexArrays(1, &VAO7);
    glDeleteBuffers(1, &VBO7);

    glfwTerminate();
    return 0;
}