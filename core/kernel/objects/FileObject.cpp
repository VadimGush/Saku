//
// Created by tsukuto on 02.04.19.
//

#include "FileObject.h"
#include <sstream>
using namespace Calc;

constexpr std::array<unsigned char, 8> png_format {0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a};
constexpr std::array<unsigned char, 3> jpg_format {0xff, 0xd8, 0xff};

FileObject::FileObject(std::string path) : Object(ObjectType::FILE), path_(std::move(path)) {
    // Первое правило загрузки файлов: никогда не верь расширениям на конце имени файла!
    std::array<unsigned char, 10> buffer{};

    // Читаем первые 10 байт
    std::ifstream file(path_);

    if (!file) {
        std::ostringstream what;
        what << "не удалось загрузить файл \"" << path_ << "\"";
        throw FileNotFound(what.str());
    }

    int counter = 0;
    for (char b; file.read(&b, sizeof(char)) && counter < buffer.size(); counter++) {
        buffer[counter] = static_cast<unsigned char>(b);
    }
    file.close();

    // Сверяем с доступными форматами
    if (std::equal(jpg_format.cbegin(), jpg_format.cend(), buffer.cbegin()))
        extension_ = "jpg";
    else if (std::equal(png_format.cbegin(), png_format.cend(), buffer.cbegin()))
        extension_ = "png";
    else
        extension_ = "bin";
}

