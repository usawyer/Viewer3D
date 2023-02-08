uniform mat4 mvp_matrix;
attribute vec3 a_position;
//uniform vec4 lines_color;
//varying vec4 colorl;

void main() {
//    colorl = lines_color;
    gl_Position = mvp_matrix * vec4(a_position.x, a_position.y, a_position.z, 1.0);
}
