#include "Biome.h"

#include <iostream>
#include <vector>
#include <FastNoise/FastNoise.h>


Biome::Biome()
{
	const auto fnSimplex = FastNoise::New<FastNoise::Simplex>();
	const auto fnFractal = FastNoise::New<FastNoise::FractalFBm>();

	fnFractal->SetSource( fnSimplex );
	fnFractal->SetOctaveCount( 5 );

	// Create an array of floats to store the noise output in
	std::vector<float> noiseOutput(16 * 16 * 16);

	// Generate a 16 x 16 x 16 area of noise
	fnFractal->GenUniformGrid3D(noiseOutput.data(), 0, 0, 0, 16, 16, 16, 0.2f, 1337);
	int index = 0;

	for (int z = 0; z < 16; z++)
	{
	    for (int y = 0; y < 16; y++)
	    {
	        for (int x = 0; x < 16; x++)
	        {
				std::cout << "x " << x << "\ty " << y << "\t: " << noiseOutput[index++] << std::endl;
	        }			
	    }
	}
}
