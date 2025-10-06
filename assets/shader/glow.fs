#version 330

in vec2 fragTexCoord; // Fragment input attribute: texture coordinate
in vec4 fragColor; // Fragment input attribute: color
out vec4 finalColor; // Fragment output: color

void main() {
    float dist = length(fragTexCoord * 2 - vec2(1)); // Hitung jarak dari tengah (0.5, 0.5)
    float glow = smoothstep(0.1, 0.8, dist); // Buat efek cahaya memudar
    float ds = 1 / glow;
    finalColor = vec4(fragColor.xyz * ds, 1);
    if (dist >= 0.8) {
        finalColor = vec4(1, 0, 0, 0);
    }

    // finalColor = vec4(fragTexCoord.x, fragTexCoord.y, 0, 1);
}
