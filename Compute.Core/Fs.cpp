
#include "Fs.h"
#include "JsExtensions.h"
#include "FreeImage.h"

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

std::string compute::readStartupFile(std::string filename)
{
    std::stringstream ss;
    ss << "module.name = '" << filename << "';";
    ss << readFile(filename);
    return ss.str();
}

void read(v8::FunctionArgs args)
{
    if (args.Length() == 1)
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
    if (args.Length() == 2)
    {
        v8::String::Utf8Value path(args[0]);
        v8::String::Utf8Value data(args[1]);

        std::ofstream file(*path);
        file << *data;
        file.close();
    }
}

void freeImage(v8::FunctionArgs args)
{
    if(args.Length() == 1)
    {
        auto bitmap = UnwrapPointer(args[0]);
        FreeImage_Unload(static_cast<FIBITMAP*>(bitmap));
    } 
}

void readImage(v8::FunctionArgs args)
{
    auto filename = GetString(args[0]);

    auto fileType = FreeImage_GetFileType(filename.c_str(), 0);
    auto bitmap = FreeImage_Load(fileType, filename.c_str());

    if (bitmap == nullptr)
    {
        std::stringstream ss;
        ss << "Could not load image: ";
        ss << filename;
        v8::Throw(ss.str());
    } 
    else
    {
    
        FIBITMAP* temp = bitmap;
        bitmap = FreeImage_ConvertTo32Bits(bitmap);
        FreeImage_Unload(temp);
        
        auto image = v8::WrapPointer(bitmap);
        image->Set(v8::NewString("filename"), args[0]);
        image->Set(v8::NewString("height"), v8::NewNumber(FreeImage_GetHeight(bitmap)));
        image->Set(v8::NewString("width"), v8::NewNumber(FreeImage_GetWidth(bitmap)));
        image->Set(v8::NewString("bpp"), v8::NewNumber(4));
        image->Set(v8::NewString("data"), v8::WrapPointer(FreeImage_GetBits(bitmap)));

        args.GetReturnValue().Set(image);
    }
}

void writeImage(v8::FunctionArgs args)
{
    auto arrayBuffer = args[1].As<v8::ArrayBuffer>();
    auto width = GetNumber(args[2]);
    auto height = GetNumber(args[3]);
    auto filename = GetString(args[0]);
   
    auto data = (unsigned char *)arrayBuffer->GetContents().Data();

    if (!filename.empty())
    {
        auto fileType = FreeImage_GetFIFFromFilename(filename.c_str());
        auto bitmap = FreeImage_ConvertFromRawBits(data, width, height, width * 4, 32, 0xFF000000, 0x00FF0000, 0x0000FF00);
        FreeImage_Save(fileType, bitmap, filename.c_str());
    }
}

void compute::registerFs(v8::Exports exports)
{
    AttachFunction(exports, "write", write);
    AttachFunction(exports, "read", read);
    AttachFunction(exports, "readImage", readImage);
    AttachFunction(exports, "writeImage", writeImage);
    AttachFunction(exports, "freeImage", freeImage);
}