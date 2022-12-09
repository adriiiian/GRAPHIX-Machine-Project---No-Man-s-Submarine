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

    void Draw(GLuint shaderProgram, GLuint VAO, std::vector<GLfloat> fullVertexData, GLuint texture) {

        unsigned int transformationLoc = glGetUniformLocation(shaderProgram, "transform");
        GLuint tex0Address = glGetUniformLocation(shaderProgram, "tex0");
        

        std::vector<glm::mat4> transformation_matrix;
        
        for (int i = 0; i < x.size(); i++) {
            transformation_matrix.push_back(glm::translate(identity_matrix, glm::vec3(x[i], y[i], z[i])));
            transformation_matrix[i] = glm::rotate(transformation_matrix[i], glm::radians(theta[i]), glm::normalize(glm::vec3(rotX[i], rotY[i], rotZ[i])));
            transformation_matrix[i] = glm::scale(transformation_matrix[i], glm::vec3(scaleX[i], scaleY[i], scaleZ[i]));

            glBindVertexArray(VAO);
            glUniformMatrix4fv(transformationLoc, 1, GL_FALSE, glm::value_ptr(transformation_matrix[i]));

            glBindTexture(GL_TEXTURE_2D, texture);
            glUniform1i(tex0Address, 0);

            glDrawArrays(GL_TRIANGLES, 0, fullVertexData.size() / 8);
        }
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

    void GeneratePointLight(GLuint shaderProgram, glm::vec3 cameraPos) {
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

    }

    //void GenerateDirectionLight(GLuint shaderProgram) {
    //    unsigned lightPosLoc = glGetUniformLocation(shaderProgram, "lightPosDir");
    //    glUniform3fv(lightPosLoc, 1, glm::value_ptr(lightPos));

    //    unsigned lightColorLoc = glGetUniformLocation(shaderProgram, "lightColorDir");
    //    glUniform3fv(lightColorLoc, 1, glm::value_ptr(lightColor));

    //    unsigned int ambientStrLoc = glGetUniformLocation(shaderProgram, "ambientStrDir");
    //    glUniform1f(ambientStrLoc, ambientStr);

    //    unsigned int ambientColorLoc = glGetUniformLocation(shaderProgram, "ambientColorDir");
    //    glUniform3fv(ambientColorLoc, 1, glm::value_ptr(ambientColor));
    //}
};

Model3D model;
Lighting lighting;
float x_mod = 0;
float y_mod = 0.f;
float z_mod = -5.f;

void Key_Callback(GLFWwindow* window, int key, int scanCode, int action, int mods) {
    if (key == GLFW_KEY_D && action == GLFW_PRESS) {
        x_mod += 10.f;
    }

    if (key == GLFW_KEY_A && action == GLFW_PRESS) {
        x_mod -= 10.f;
    }

    if (key == GLFW_KEY_S) {
        y_mod += 0.2f;
    }

    if (key == GLFW_KEY_W) {
        y_mod -= 0.2f;
    }
}

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

    std::string path = "3D/bird.obj";
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

    int img_width, img_height, color_channels;
    unsigned char* tex_bytes = stbi_load("3D/wood.jpg", &img_width, &img_height, &color_channels, 0);

    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width, img_height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_bytes);

    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(tex_bytes);

    glEnable(GL_DEPTH_TEST);

    glfwSetKeyCallback(window, Key_Callback);

    std::fstream vertSrc("Shaders/sample.vert");
    std::stringstream vertBuff;
    vertBuff << vertSrc.rdbuf();
    std::string vertString = vertBuff.str();
    const char* v = vertString.c_str();

    std::fstream fragSrc("Shaders/sample.frag");
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
                GL_RGB,
                w,
                h,
                0,
                GL_RGB,
                GL_UNSIGNED_BYTE,
                data
            );
        }

        stbi_image_free(data);
    }
    stbi_set_flip_vertically_on_load(true);

    // skybox fragment shader
    //Vertex Shader
    std::fstream skybox_vertSrc("Shaders/skybox.vert");
    std::stringstream skybox_vertBuff;
    skybox_vertBuff << skybox_vertSrc.rdbuf();
    std::string skybox_vertString = skybox_vertBuff.str();
    const char* skybox_v = skybox_vertString.c_str();

    //Fragment shader
    std::fstream skybox_fragSrc("Shaders/skybox.frag");
    std::stringstream skybox_fragBuff;
    skybox_fragBuff << skybox_fragSrc.rdbuf();
    std::string skybox_fragString = skybox_fragBuff.str();
    const char* skybox_f = skybox_fragString.c_str();

    GLuint skybox_vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(skybox_vertexShader, 1, &skybox_v, NULL);
    glCompileShader(skybox_vertexShader);

    GLuint skybox_fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(skybox_fragShader, 1, &skybox_f, NULL);
    glCompileShader(skybox_fragShader);


    GLuint skybox_shaderProg = glCreateProgram();
    glAttachShader(skybox_shaderProg, skybox_vertexShader);
    glAttachShader(skybox_shaderProg, skybox_fragShader);

    glLinkProgram(skybox_shaderProg);

    // LOADING OBJECTS
    bool success = tinyobj::LoadObj(
        &attributes,
        &shapes,
        &materials,
        &warning,
        &error,
        path.c_str()
    );

    std::vector<GLfloat> fullVertexData;
    for (int i = 0; i < shapes[0].mesh.indices.size(); i++) {
        tinyobj::index_t vData = shapes[0].mesh.indices[i];

        int vertexIndex = vData.vertex_index * 3;
        int normalIndex = vData.normal_index * 3;
        int uvIndex = vData.texcoord_index * 2;

        fullVertexData.push_back(attributes.vertices[(vData.vertex_index * 3)]);
        fullVertexData.push_back(attributes.vertices[(vData.vertex_index * 3) + 1]);
        fullVertexData.push_back(attributes.vertices[(vData.vertex_index * 3) + 2]);
        fullVertexData.push_back(attributes.normals[(vData.normal_index * 3)]);
        fullVertexData.push_back(attributes.normals[(vData.normal_index * 3) + 1]);
        fullVertexData.push_back(attributes.normals[(vData.normal_index * 3) + 2]);
        fullVertexData.push_back(attributes.texcoords[(vData.texcoord_index * 2)]);
        fullVertexData.push_back(attributes.texcoords[(vData.texcoord_index * 2) + 1]);
    }

    GLuint VAO, VBO;
    //Generate and Assign ID to VAO
    glGenVertexArrays(1, &VAO);
    //Generate and Assign ID to VBO
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(GL_FLOAT) * fullVertexData.size(), //Indices of the Array
        fullVertexData.data(), //array itself
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0, //Poosition
        3, //XYZ,
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

    // bird model
    model.x.push_back(4.0f);
    model.y.push_back(-4.0f);
    model.z.push_back(0.0f);
    model.rotX.push_back(1.0f);
    model.rotY.push_back(0.0f);
    model.rotZ.push_back(0.0f);
    model.theta.push_back(90.0f);
    model.scaleX.push_back(0.75f);
    model.scaleY.push_back(0.75f);
    model.scaleZ.push_back(0.75f);

    glm::mat4 projection_matrix = glm::perspective(glm::radians(60.f), screenHeight / screenWidth, 0.1f, 100.f);

    lighting.lightDir = glm::vec3(0, -10, 0);
    lighting.lightColor = glm::vec3(1, 1, 1);
    lighting.ambientColor = glm::vec3(1, 1, 1);
    lighting.ambientStr = 0.1f;
    lighting.specStr = 1.f;
    lighting.specPhong = 16.0f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /*theta = x_mod;*/
        /*theta += 0.01f;*/
        /*z = z_mod;*/

        glm::vec3 cameraPos = glm::vec3(x_mod, 0, 10.f);
        glm::mat4 cameraPosMatrix = glm::translate(glm::mat4(1.0f), cameraPos * -1.f);

        glm::vec3 worldUp = glm::vec3(0, 1.0f, 0);
        glm::vec3 cameraCenter = glm::vec3(0, 0.0f, 0);

        glm::mat4 viewMatrix = glm::lookAt(cameraPos, cameraCenter, worldUp);

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

        lighting.GeneratePointLight(shaderProgram, cameraPos);

        unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection_matrix));

        unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

        model.Draw(shaderProgram, VAO, fullVertexData, texture);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}