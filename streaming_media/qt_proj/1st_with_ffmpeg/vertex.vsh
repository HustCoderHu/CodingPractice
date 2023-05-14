//attribute highp vec4 qt_Vertex;
//attribute highp vec4 qt_MultiTexCoord0;
//uniform highp mat4 qt_ModelViewProjectionMatrix;
//varying highp vec4 qt_TexCoord0;

//void main(void)
//{
//    gl_Position = qt_ModelViewProjectionMatrix * qt_Vertex;
//    qt_TexCoord0 = qt_MultiTexCoord0;
//}

#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCord;
out vec2 TexCord;    // 纹理坐标
void main()
{
    gl_Position =  vec4(aPos.x, -aPos.y, aPos.z, 1.0);   // 图像坐标和OpenGL坐标Y轴相反，
    TexCord = aTexCord;
}
