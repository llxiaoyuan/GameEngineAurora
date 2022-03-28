#version 330 core
    precision mediump float;

    uniform vec4 color;

    void main () {
        gl_FragColor = color;
    }