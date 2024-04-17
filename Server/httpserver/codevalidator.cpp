#include "codevalidator.h"

codevalidator::codevalidator()
{
    validCodes.insert("010D429BBA");
    validCodes.insert("0A1B2C3D4E");
}

bool codevalidator::isValid(const QString& code) {
    // Check if the code is valid
    return validCodes.contains(code);
}
