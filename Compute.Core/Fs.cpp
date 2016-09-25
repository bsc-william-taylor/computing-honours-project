
#include "Fs.h"
#include "JsExtensions.h"

std::string compute::readFile(std::string filename)
{
    std::ifstream file(filename);
    std::string data;

    if (file.is_open())
    {
        std::string temp;
        while (getline(file, temp))
        {
            data += temp + "\n";
        }
    }

    file.close();
    return data;
}

void read(v8::FunctionArgs args)
{
    if(args.Length() == 1)
    {
        v8::String::Utf8Value path(args[0]);

        Poco::Path pocoPath(*path);
        Poco::File pocoFile(*path);

        const auto fileSize = std::to_string(pocoFile.getSize());
        const auto file = v8::Object::New(args.GetIsolate());

        file->Set(v8::NewString("path"), v8::NewString(pocoPath.toString(Poco::Path::PATH_UNIX)));
        file->Set(v8::NewString("size"), v8::NewString(fileSize));
        file->Set(v8::NewString("extension"), v8::NewString(pocoPath.getExtension()));
        file->Set(v8::NewString("filename"), v8::NewString(pocoPath.getFileName()));
        file->Set(v8::NewString("contents"), v8::NewString(compute::readFile(*path)));

        args.GetReturnValue().Set(file);
    }
}

void write(v8::FunctionArgs args)
{
    if(args.Length() == 2)
    {
        v8::String::Utf8Value path(args[0]);
        v8::String::Utf8Value data(args[1]);

        std::ofstream file(*path);
        file << *data;
        file.close();
    }
}

void compute::registerFs(v8::Local<v8::Object>& object)
{
    AttachFunction(object, "write", write);
    AttachFunction(object, "read", read);
}