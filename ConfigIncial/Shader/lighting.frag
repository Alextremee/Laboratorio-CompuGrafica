#version 330 core
out vec4 FragColor;

// Entradas del Vertex Shader
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

// Samplers para las texturas (la clase Model envía "texture_diffuse1", "texture_specular1", etc.)
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1; // Para los brillos

// Propiedad de material (brillo)
uniform float material_shininess; 

// Estructura para nuestras luces
struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

// ¡AQUÍ ESTÁ EL CAMBIO! Recibimos DOS luces
uniform Light sun;
uniform Light moon;

// Posición de la cámara
uniform vec3 viewPos;

// --- Función para calcular la contribución de UNA luz ---
// Esta función calcula la luz usando las texturas
vec3 CalcLight(Light light, vec3 norm, vec3 viewDir, vec3 fragPos) {
    
    // Obtenemos el color base de la textura
    vec3 diffuseColor = texture(texture_diffuse1, TexCoords).rgb;
    // Obtenemos el color del brillo de la textura (si no hay, suele ser negro)
    vec3 specularColor = texture(texture_specular1, TexCoords).rgb;

    // Luz Ambiental (usa el color de la textura)
    vec3 ambient = light.ambient * diffuseColor;
    
    // Luz Difusa (usa el color de la textura)
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * diffuseColor;
    
    // Luz Especular (usa el mapa especular)
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material_shininess);
    vec3 specular = light.specular * spec * specularColor;
    
    return (ambient + diffuse + specular);
}

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // 1. Calcular el efecto del sol
    vec3 result = CalcLight(sun, norm, viewDir, FragPos);
    
    // 2. Añadir el efecto de la luna
    result += CalcLight(moon, norm, viewDir, FragPos);
    
    FragColor = vec4(result, 1.0);
}