if not exist .\build (
    mkdir build
)
gcc src/main.c src/nextstep.c src/render.c src/collisioncalculation.c src/particle.c -o build/particleMadness.exe -O1 -Wall -std=c99 -Wno-missing-braces -I src/include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
build\particleMadness.exe