#include <string>

class ErrorHandler{

private:
    /* data */

    bool saveErrorToSdCard();

public:

    ErrorHandler(/* args */);
    ~ErrorHandler();

    
    bool handelError(std::string error);

};



