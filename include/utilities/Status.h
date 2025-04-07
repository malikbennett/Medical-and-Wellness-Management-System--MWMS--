enum class StatusCode {
    Ok,
    FileError,
    KeyError,
    UsernameNotFound,
    IncorrectPassword,
    RoleMismatch,
    InvalidRole,
    UnknownError
};

struct Result {
    bool ok() const { return code == StatusCode::Ok; }
    const char *type() const { return this->statusType; }
    const char *message() const { return this->statusMessage; }
    Result(StatusCode code)
        : code(code)
    {
        this->statusType = StatusType(code);
        this->statusMessage = StatusMessage(code);
    };

private:
    StatusCode code;
    const char* statusType;
    const char* statusMessage;
    const char* StatusMessage(StatusCode code) {
    switch (code) {
        case StatusCode::Ok: return "No error.";
        case StatusCode::FileError: return "Failed to open file.";
        case StatusCode::KeyError: return "Failed to read the encryption key.";
        case StatusCode::UsernameNotFound: return "Username not found.";
        case StatusCode::IncorrectPassword: return "Password is incorrect.";
        case StatusCode::RoleMismatch: return "User role does not match.";
        case StatusCode::InvalidRole: return "Selected role is invalid.";
        default: return "An unknown error occurred.";
    }
}
    const char* StatusType(StatusCode code) {
    switch (code) {
        case StatusCode::Ok: return "No Error";
        case StatusCode::FileError: return "File Error";
        case StatusCode::KeyError: return "Encryption Key Error";
        case StatusCode::UsernameNotFound: return "Login Error";
        case StatusCode::IncorrectPassword: return "Login Error";
        case StatusCode::InvalidRole: return "Login Error";
        case StatusCode::RoleMismatch: return "Login Error";
        default: return "Unknown Error";
    }
}
};
