
#include "TextFile.h"

v8::Persistent<v8::Function> TextFile::constructor;

TextFile::TextFile()
{
}

TextFile::~TextFile()
{
}

void TextFile::create(v8::Local<v8::ObjectTemplate>& cpp, v8::Isolate * isolate)
{
	auto templateObject = newTemplate(newInstance, "TextFile");

	templateObject->PrototypeTemplate()->Set(V8_String("read"), v8::FunctionTemplate::New(isolate, read)->GetFunction());
	templateObject->InstanceTemplate()->SetAccessor(V8_String("contents"), getContents, setContents);
	templateObject->InstanceTemplate()->SetAccessor(V8_String("filename"), getFilename, setFilename);
	templateObject->InstanceTemplate()->SetAccessor(V8_String("path"), getPath, setPath);
	templateObject->InstanceTemplate()->SetAccessor(V8_String("ext"), getExt, setExt);

	makeConstructor(cpp, templateObject, constructor, "TextFile");
}

void TextFile::setExt(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
	auto that = info.This();
	auto obj = unwrap(that);
	obj->ext = *v8::String::Utf8Value(value);
}

void TextFile::getExt(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	auto that = info.This();
	auto obj = unwrap(that);
	info.GetReturnValue().Set(V8_String(obj->ext.c_str()));
}

void TextFile::setContents(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
	auto that = info.This();
	auto obj = unwrap(that);
	obj->contents = *v8::String::Utf8Value(value);
}

void TextFile::getContents(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	auto that = info.This();
	auto obj = unwrap(that);
	info.GetReturnValue().Set(V8_String(obj->contents.c_str()));
}

void TextFile::setFilename(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
	auto that = info.This();
	auto obj = unwrap(that);
	obj->filename = *v8::String::Utf8Value(value);
}

void TextFile::getFilename(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	auto that = info.This();
	auto obj = unwrap(that);
	info.GetReturnValue().Set(V8_String(obj->filename.c_str()));
}

void TextFile::setPath(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
	auto that = info.This();
	auto obj = unwrap(that);
	obj->path = *v8::String::Utf8Value(value);
}

void TextFile::getPath(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	auto that = info.This();
	auto obj = unwrap(that);
	info.GetReturnValue().Set(V8_String(obj->path.c_str()));
}

void TextFile::read(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	auto that = unwrap(args);
	v8::String::Utf8Value path(args[0]);

	auto filePath = Poco::Path(Poco::Path::current());
	filePath.append(*path);
	std::ifstream file(filePath.toString());
	std::string data;

	if (file.is_open()) {
		std::string temp;
		while (getline(file, temp)) {
			data += temp + "\n";
		}

		file.close();
	}

	that->filename = filePath.getBaseName();
	that->path = filePath.absolute().toString();
	that->ext = filePath.getExtension();
	that->contents = data;
}

void TextFile::newInstance(const v8::FunctionCallbackInfo<v8::Value>& info)
{
	v8::HandleScope scope(info.GetIsolate());
	auto obj = new TextFile();
	auto that = info.This();
	obj->wrap(that);
	info.GetReturnValue().Set(that);
}