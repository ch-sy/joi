#version 330 core

// Interpolated values from the vertex shaders
in vec2 texCoord;

// Ouput data
out vec4 color;

// Values that stay constant for the whole mesh.
uniform sampler2D u_sTexture;

void main(){

    // Output color = color of the texture at the specified UV
    color = texture( u_sTexture, texCoord ) * vec4(1.0,1.0,1.0,1.0);
}