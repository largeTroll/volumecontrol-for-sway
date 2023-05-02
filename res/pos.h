// This file contains the pictograms (audio/backlight symbol), as well as
// for the bar.

// Positions of the audio pictogram
float audioposition[] = {
        -1.0f,  0.5f, // 0
        -1.0f, -0.5f, // 1
         0.5f, -0.5f, // 2
         1.0f, -1.0f, // 3
         1.0f,  1.0f, // 4
         0.5f,  0.5f, // 5
};

unsigned int audioindex[] = {
        0, 1, 2,
        0, 2, 5,
        5, 2, 3,
        3, 4, 5
};

// 2D positions for the backlight pictogram
float lightposition[] = {
        // Frame
        -1.0f,  0.6f, // 00 Outer
        -1.0f, -0.6f, // 01
         1.0f, -0.6f, // 02
         1.0f,  0.6f, // 03
        -0.9f,  0.5f, // 04 Inner
        -0.9f, -0.5f, // 05
         0.9f, -0.5f, // 06
         0.9f,  0.5f, // 07

         // Bars
         -0.9f,  0.0f, // 08 1
         -0.9f, -0.1f, // 09
         -0.5f, -0.5f, // 10
         -0.4f, -0.5f, // 11
         -0.9f,  0.5f, // 12 2
         -0.9f,  0.4f, // 13
          0.0f, -0.5f, // 14
          0.1f, -0.5f, // 15
         -0.4f,  0.5f, // 16 3
         -0.5f,  0.5f, // 17
          0.5f, -0.5f, // 18
          0.6f, -0.5f, // 19
          0.1f,  0.5f, // 20 4
          0.0f,  0.5f, // 21
          0.9f, -0.4f, // 22
          0.9f, -0.3f, // 23
          0.6f,  0.5f, // 24 5
          0.5f,  0.5f, // 25
          0.9f,  0.1f, // 26
          0.9f,  0.2f, // 27
};

unsigned int lightindex[] = {
        // Frame
        0,1,5, // Links
        5,4,0,
        1,2,6, // Unten
        6,5,1,
        2,3,7, // Rechts
        7,6,2,
        3,0,4, // Oben
        4,7,3,

        // Bars
        8,9,10, // 1
        10,11,8,
        12,13,14, // 2
        14,15,12,
        16,17,18, // 3
        18,19,16,
        20,21,22, // 4
        22,23,20,
        24,25,26, // 5
        26,27,24
};

// Bar positions, formated like this:
// vec2 position, float percentage between the two ends, float brightness on that end
float barposition[] = {
        -0.75f, -0.5f,  0.0f, 0.2f, // 0
        -0.75f, -0.75f, 0.0f, 0.2f, // 1
         0.75f, -0.75f, 1.0f, 0.9f, // 2
         0.75f, -0.5f,  1.0f, 0.9f  // 3
};

// Indices in the bar postions array
unsigned int barindex[] = {
        0, 1, 2,
        2, 3, 0
};