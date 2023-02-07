#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;
out vec4 ourColor;

uniform int shadingType;

uniform mat4 Model, View, Projection;
uniform mat3 NormalMatrix;

// phong calcolato pre-fragment shading
// modelli di shading calcolati qui.

////////////////////////////////////////////////////////////////////////////////

void applyPhongShading()
{
    
}

////////////////////////////////////////////////////////////////////////////////

void main()
{
    gl_Position = Projection * View * Model * vec4(aPos, 1.0);
    TexCoord = aTexCoord;

    FragPos = vec3(Model * vec4(aPos, 1.0));


    switch (shadingType)
    {
        case -1: // Phong lighting model with Phong shading
        case -2: // Blinn-Phong lighting model with Phong shading
            // Per usare lo shading di Phong
            /* Applicheremo alla normale di ogni vertice in coordinate 
            dell’oggetto la trasposta dell’ inversa della matrice model view (M−1)T 
            (dove M=View Model). La normale trasformata sarà data in output e 
            rappresenterà quindi l’input del fragment shader. Quindi le normali 
            saranno interpolate sui lati della primitiva prima di arrivare nel 
            fragment shader e sarà nel fragment shader che si calcolerà 
            l’equazione dell’illuminazione e quindi il colore per ogni frammento
            della scena.*/
            mat3 VMmatrix = mat3(transpose(inverse(View * Model)));
            Normal = VMmatrix * aNormal;
            break;
        default:
            Normal = NormalMatrix * aNormal;
            break;
    }

    ourColor = aColor;

}