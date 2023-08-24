#ifndef CERVER_ENUMS_H
#define CERVER_ENUMS_H

enum ReturnType {
    OK,
    ERROR,
    FAILURE,
    UNAUTHORIZED
};

typedef enum ReturnType ReturnType;

typedef void (*simple_callback)(void);

#endif /* CERVER_ENUMS_H */
