/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#include <cstring>

namespace BinaryData
{

//================== trash-solid.png ==================
static const unsigned char temp_binary_data_0[] =
{ 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,24,0,0,0,24,8,6,0,0,0,224,119,61,248,0,0,0,6,98,75,71,68,0,255,0,255,0,255,160,189,167,147,0,0,1,59,73,68,65,84,72,137,189,213,191,46,68,65,24,5,240,223,90,34,116,10,10,53,141,87,208,168,136,134,151,
80,18,207,33,58,148,36,122,21,45,137,74,178,201,86,178,254,188,129,134,40,109,196,186,171,184,67,214,228,222,187,119,239,13,39,153,102,206,55,231,156,204,124,51,195,31,163,81,162,102,2,187,88,193,100,152,123,199,53,14,240,81,55,196,41,18,180,112,25,70,
43,204,157,212,21,159,70,15,123,25,220,190,52,253,116,145,192,216,16,131,57,52,241,152,193,221,99,60,212,228,98,240,12,118,176,17,241,83,88,198,3,158,34,110,30,75,184,65,55,226,46,112,40,36,40,66,23,87,57,220,83,134,233,255,35,110,211,109,108,214,212,
60,199,81,30,121,38,109,191,126,197,145,4,141,31,196,93,116,87,51,61,116,138,12,58,202,221,238,60,52,98,131,24,139,170,111,207,247,88,40,50,24,195,91,13,241,174,104,87,226,45,74,164,183,182,95,148,34,7,125,233,237,78,138,12,224,54,46,42,137,36,172,253,
133,44,131,142,244,253,25,21,77,25,7,156,103,80,21,165,214,206,170,126,200,133,47,235,32,94,42,136,63,103,9,229,253,7,109,124,150,77,19,106,219,35,212,91,151,118,69,207,240,228,189,80,187,150,37,84,244,44,172,98,11,51,67,194,188,226,88,250,87,255,63,
190,0,93,205,139,14,227,37,19,76,0,0,0,0,73,69,78,68,174,66,96,130,0,0 };

const char* trashsolid_png = (const char*) temp_binary_data_0;


const char* getNamedResource (const char* resourceNameUTF8, int& numBytes);
const char* getNamedResource (const char* resourceNameUTF8, int& numBytes)
{
    unsigned int hash = 0;

    if (resourceNameUTF8 != nullptr)
        while (*resourceNameUTF8 != 0)
            hash = 31 * hash + (unsigned int) *resourceNameUTF8++;

    switch (hash)
    {
        case 0x4916665d:  numBytes = 390; return trashsolid_png;
        default: break;
    }

    numBytes = 0;
    return nullptr;
}

const char* namedResourceList[] =
{
    "trashsolid_png"
};

const char* originalFilenames[] =
{
    "trash-solid.png"
};

const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8)
{
    for (unsigned int i = 0; i < (sizeof (namedResourceList) / sizeof (namedResourceList[0])); ++i)
        if (strcmp (namedResourceList[i], resourceNameUTF8) == 0)
            return originalFilenames[i];

    return nullptr;
}

}
