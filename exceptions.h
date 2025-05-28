//
// Created by DanCo on 5/28/2025.
//

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <stdexcept>

using namespace std;
class not_found_exception:public exception {
    string message;
public:
    not_found_exception(string message);
    const char*what()const noexcept override;
};
class syntax_error:public exception {
public:
    const char*what()const noexcept override;
};

class Resistant_exception:public exception{
    public:
        const char*what();
};
class Resistor_negative_resistance_exception:public Resistant_exception {
    public:
    const char*what()const noexcept override;
};
class Resistor_not_found_for_deleting_exception:public Resistant_exception {
    public:
    const char*what()const noexcept override;
};
class Resistor_repeated_exception:public Resistant_exception {
    string message;
    public:
    Resistor_repeated_exception(string message);
    const char*what()const noexcept override;
};
class Capacitor_exception:public exception {
    public:
    const char*what();
};
class Capacitor_negative_capacity_exception:public Capacitor_exception {
    public:
    const char*what()const noexcept override;
};

class Capacitor_not_found_for_deleting_exception:public Capacitor_exception {
public:
    const char*what()const noexcept override;
};
class Capacitor_repeated_exception:public Capacitor_exception {
    string message;
    public:
    Capacitor_repeated_exception(string message);
    const char*what()const noexcept override;
};
class Inductor_exception:public exception {
    public:
    const char*what()const noexcept override;
};
class Inductor_negative_exception:public Inductor_exception {
    public:
    const char*what()const noexcept override;
};

class Inductor_not_found_for_deleting_exception:public Inductor_exception {
    public:
    const char*what()const noexcept override;
};
class Inductor_repeated_exception:public Inductor_exception {
    string message;
    public:
    Inductor_repeated_exception(string message);
    const char*what()const noexcept override;
};
class Diode_exception:public exception {
    public:
    const char*what();
};
class Diode_wrong_modality:public Diode_exception {
    string message;
    public:
    Diode_wrong_modality(string message);
    const char*what()const noexcept override;
};
class Diode_not_found_for_deleting_exception:public Diode_exception {
    public:
    const char*what()const noexcept override;
};
class Diode_repeated_exception:public Diode_exception {
    string message;
    public:
    Diode_repeated_exception(string message);
    const char*what()const noexcept override;
};
class
#endif //EXCEPTIONS_H
