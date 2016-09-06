
#include "Fs.h"

std::string raster::readFile(const char * filename)
{
    std::ifstream file(filename);
    std::string data;

    if (file.is_open()) {
        std::string temp;
        while (getline(file, temp)) {
            data += temp + "\n";
        }

        file.close();
    }

    return data;
}

void raster::registerFs(v8::Local<v8::Object>& object) {
    const auto isolate = v8::Isolate::GetCurrent();

    TextFile::create(object, isolate);
    //Image::create(object, isolate);
}