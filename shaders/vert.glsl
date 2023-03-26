#version 330 core

//in vec2 position;
//in float color;
//
//out float Color;

// controls the scale of the vertices
uniform float scale;

// Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Colors
layout (location = 1) in vec3 aColor;
// Texture Coordinates
layout (location = 2) in vec2 aTex;

// Color output for frag shader
out vec3 color;
// Texture coords output for frag shader
out vec2 texCoord;

void main()
{
    // output positions/coordinates of vertex
    gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
    // assign color from vertex data to output variable
    color = aColor;
    // assign texture coordinates from vertex data to output variable
    texCoord = aTex;


//    Color = color;
//    gl_Position = vec4(position, 0.0f, 1.0f);
//    gl_Position = position;
//    gl_PointSize = 100.0;
}
