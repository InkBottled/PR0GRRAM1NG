#include <fstream>
#include <string>
#include <iostream>
#include "lodepng.h" /* MUST INCLUDE lodepng.h AND lodepng.cpp !!!! */

using namespace std;
using namespace lodepng;

int main()
{
    // VARS
    string filename1 = "";
    string filename2 = "";

    // IN

    wcout << "Input source image path: ";
    cin >> filename1;
    wcout << "Input cover image path: ";
    cin >> filename2;

    cout << endl << "Make sure you put in the FULL pathname!" << endl;

    std::vector<unsigned char> image1; // The raw pixels
    std::vector<unsigned char> image2; // The raw pixels

    std::vector<unsigned char> result; // Final image

    unsigned width1, height1;
    unsigned width2, height2;

    // Decode

    unsigned error1 = lodepng::decode(image1, width1, height1, filename1);
    unsigned error2 = lodepng::decode(image2, width2, height2, filename2);

    // Fancy display for size

    cout << "\n> Source image:\n|  > Width: " << width1 << "\n|  > Height: " << height1;
    cout << "\n> Cover image:\n|  > Width: " << width2 << "\n|  > Height: " << height2;

    // NOT Fancy error

    if (width1 != width2 || height1 != height2)
    {
        wcout << "\n\nError!\nNot the same width / height!" << endl;
        return 1;
    }

    // If there's an error, display it

    if (error1) cout << "\nDecoder error " << error1 << ": " << lodepng_error_text(error1) << endl;
    if (error2) cout << "\nDecoder error " << error2 << ": " << lodepng_error_text(error2) << endl;

    wcout << endl;

    vector<bool> LSD;

    for (int i = 0; i < image1.size(); i++)
    {
        LSD.push_back((bool)image1.at(i) % 2);
    }

    int ImgS = image2.size();

    for (int i = 0; ImgS > i; i++)
    {
        if ((i + 1) % 4 != 0)
        {
            image2[i] = ((int)image2.at(i)) / 2 * 2 + ((int)LSD[i]);
        }
    }

    string outDir = "";
    outDir.assign(filename1);
    for (int i = outDir.length() - 1; i > 0; i--)
    {
        if (outDir.at(i) == '\\')
        {
            break;
            cout << outDir;
        }
        else
        {
            outDir.erase(outDir.length() - 1);
            cout << outDir;
        }
    }

    cout << outDir;

    lodepng::encode(outDir + "result.ship.png", image2, width1, height1);

    return 0;
}
