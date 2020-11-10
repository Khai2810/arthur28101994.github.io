#ifndef COMPILER_H
#define COMPILER_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

/**
* @brief The memory class AUTOMATIC shall be provided as empty definition, used for the declaration
*        of local pointers.
*/
#define AUTOMATIC

/**
* @brief The memory class TYPEDEF shall be provided as empty definition. This memory class shall be
*        used within type definitions, where no memory qualifier can be specified. This can be
*        necessary for defining pointer types, with e.g. P2VAR, where the macros require two
*        parameters. First parameter can be specified in the type definition (distance to the memory
*        location referenced by the pointer), but the second one (memory allocation of the pointer
*        itself) cannot be defined at this time. Hence memory class TYPEDEF shall be applied.
*/
#define TYPEDEF

/**
* @brief The compiler abstraction shall provide the NULL_PTR define with a void pointer to zero
*        definition.
*/
#define NULL_PTR ((void *)0)

/**************************************** Green Hills *********************************************/
#ifdef _GREENHILLS_
    /* Prototypes for intrinsic functions */
    /**
    * @brief The compiler abstraction shall provide the INLINE define for abstraction of the keyword
    *        inline.
    */
  /*
    * @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
    *    a constant, a parenthesised expression
    */    
    #define INLINE              __inline

    /**
    * @brief The compiler abstraction shall provide the LOCAL_INLINE define for abstraction of the
    *       keyword inline in functions with "static" scope
    */
  /*
    * @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
    *    a constant, a parenthesised expression
    */        
    #define LOCAL_INLINE            static __inline

    /**
    * @brief Compiler abstraction for specifying an interrupt handler.
    */
  /*
    * @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
    *    a constant, a parenthesised expression
    */        
    #define INTERRUPT_FUNC      __interrupt
#endif /* #ifdef _GREENHILLS_ */

/**************************************** Wind River Diab *****************************************/
#ifdef _DIABDATA
    /* Prototypes for intrinsic functions */
    /**
    * @brief The compiler abstraction shall provide the INLINE define for abstraction of the keyword
    *        inline.
    */
  /*
    * @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
    *    a constant, a parenthesised expression
    */        
    #define INLINE              __inline__

    /**
    * @brief The compiler abstraction shall provide the LOCAL_INLINE define for abstraction of the
    *       keyword inline in functions with "static" scope
    */
  /*
    * @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
    *    a constant, a parenthesised expression
    */        
    #define LOCAL_INLINE            static __inline__

    /**
    * @brief Compiler abstraction for specifying an interrupt handler.
    */
  /*
    * @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
    *    a constant, a parenthesised expression
    */        
    #define INTERRUPT_FUNC      __interrupt__
#endif /* #ifdef _DIABDATA_ */

/*************************************** CodeWarrior **********************************************/
#ifdef _CODEWARRIOR_
    /* Prototypes for intrinsic functions */
    /**
    * @brief The compiler abstraction shall provide the INLINE define for abstraction of the keyword
    *        inline.
    */
  /*
    * @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
    *    a constant, a parenthesised expression
    */        
    #define INLINE              inline

    /**
    * @brief The compiler abstraction shall provide the LOCAL_INLINE define for abstraction of the
    *       keyword inline in functions with "static" scope
    */
  /*
    * @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
    *    a constant, a parenthesised expression
    */        
    #define LOCAL_INLINE            static inline

     /**
    * @brief Compiler abstraction for specifying an interrupt handler.
    */
  /*
    * @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
    *    a constant, a parenthesised expression
    */        
    #define INTERRUPT_FUNC      __declspec(interrupt nowarn)
 #endif /* #ifdef _CODEWARRIOR_ */

/*************************************** Cosmic ***************************************************/
#ifdef _COSMIC_
    /* Prototypes for intrinsic functions */
    /**
    * @brief The compiler abstraction shall provide the INLINE define for abstraction of the keyword
    *        inline.
    */
  /*
    * @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
    *    a constant, a parenthesised expression
    */        
    #define INLINE @inline

    /**
    * @brief The compiler abstraction shall provide the LOCAL_INLINE define for abstraction of the
    *       keyword inline in functions with "static" scope
    */
  /*
    * @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
    *    a constant, a parenthesised expression
    */        
    #define LOCAL_INLINE            static @inline

    /**
    * @brief Compiler abstraction for specifying an interrupt handler.
    */
  /*
    * @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
    *    a constant, a parenthesised expression
    */        
    #define INTERRUPT_FUNC @interrupt
#endif /* #ifdef _COSMIC_*/
/*************************************** HighTec **********************************************/
#ifdef _HITECH_
    /* Prototypes for intrinsic functions */
    /**
    * @brief The compiler abstraction shall provide the INLINE define for abstraction of the keyword
    *        inline.
    */
  /*
    * @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
    *    a constant, a parenthesised expression
    */    
    #define INLINE              __inline

/**
    * @brief The compiler abstraction shall provide the LOCAL_INLINE define for abstraction of the
    *       keyword inline in functions with "static" scope
*/
  /*
    * @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
    *    a constant, a parenthesised expression
    */    
    #define LOCAL_INLINE            static __inline

    /**
    * @brief Compiler abstraction for specifying an interrupt handler.
    */
  /*
    * @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
    *    a constant, a parenthesised expression
    */    
    #define INTERRUPT_FUNC      __attribute__((interrupt));
#endif /* #ifdef _HITECH_ */

/**************************************** Linaro *********************************************/
#ifdef _LINARO_
    /* Prototypes for intrinsic functions */
    /**
    * @brief The compiler abstraction shall provide the INLINE define for abstraction of the keyword
    *        inline.
    */
    /*
    * @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
    *    a constant, a parenthesised expression
    */    
    #define INLINE                  inline __attribute__((always_inline))

    /**
    * @brief The compiler abstraction shall provide the LOCAL_INLINE define for abstraction of the
    *       keyword inline in functions with "static" scope
    */
    /*
    * @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
    *    a constant, a parenthesised expression
    */        
    #define LOCAL_INLINE            static inline __attribute__((always_inline))

    /**
    * @brief Compiler abstraction for specifying an interrupt handler.
    */
    /*
    * @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
    *    a constant, a parenthesised expression
    */        
    #define INTERRUPT_FUNC     
#endif /* #ifdef _LINARO_ */
/**************************************** DS5 *************************************************/
#ifdef _ARM_DS5_
    /* Prototypes for intrinsic functions */
    /**
    * @brief The compiler abstraction shall provide the INLINE define for abstraction of the keyword
    *        inline.
    */
  /*
    * @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
    *    a constant, a parenthesised expression
    */    
    #define INLINE              __inline

    /**
    * @brief The compiler abstraction shall provide the LOCAL_INLINE define for abstraction of the
    *       keyword inline in functions with "static" scope
    */
  /*
    * @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
    *    a constant, a parenthesised expression
    */        
    #define LOCAL_INLINE            static __inline

    /**
    * @brief Compiler abstraction for specifying an interrupt handler.
    */
  /*
    * @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
    *    a constant, a parenthesised expression
    */        
    #define INTERRUPT_FUNC
#endif /* #ifdef _ARM_DS5_ */

/**************************************** IAR *************************************************/
#ifdef _IAR_
    /* Prototypes for intrinsic functions */
    /**
    * @brief The compiler abstraction shall provide the INLINE define for abstraction of the keyword
    *        inline.
    */
  /*
    * @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
    *    a constant, a parenthesised expression
    */    
    #define INLINE              inline

    /**
    * @brief The compiler abstraction shall provide the LOCAL_INLINE define for abstraction of the
    *       keyword inline in functions with "static" scope
    */
  /*
    * @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
    *    a constant, a parenthesised expression
    */        
    #define LOCAL_INLINE            static inline

    /**
    * @brief Compiler abstraction for specifying an interrupt handler.
    */
  /*
    * @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
    *    a constant, a parenthesised expression
    */        
    #define INTERRUPT_FUNC
#endif /* #ifdef _IAR_ */


/**
* @brief The compiler abstraction shall define the FUNC macro for the declaration and definition of
*        functions, that ensures correct syntax of function declarations as required by a specific
*        compiler.
*/
/*
* @violates @ref Compiler_h_REF_1 A function should be used in
* preference to a function-like macro.
*/
/*
* @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
*    a constant, a parenthesised expression
*/
/*
* @violates @ref Compiler_h_REF_4 In the definition of a function-like macro each instance of a
*  parameter shall be enclosed in parentheses
*/
#define FUNC(rettype, memclass) rettype

/**
* @brief The compiler abstraction shall define the P2VAR macro for the declaration and definition of
*        pointers in RAM, pointing to variables.
*/
/*
* @violates @ref Compiler_h_REF_1 A function should be used in
* preference to a function-like macro.
*/
/*
* @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
*    a constant, a parenthesised expression
*/
/*
* @violates @ref Compiler_h_REF_4 In the definition of a function-like macro each instance of a
*  parameter shall be enclosed in parentheses
*/
#define P2VAR(ptrtype, memclass, ptrclass) ptrtype *

/**
* @brief The compiler abstraction shall define the P2CONST macro for the declaration and definition
*        of pointers in RAM pointing to constants.
*/
/*
* @violates @ref Compiler_h_REF_1 A function should be used in
* preference to a function-like macro.
*/
/*
* @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
*    a constant, a parenthesised expression
*/
/*
* @violates @ref Compiler_h_REF_4 In the definition of a function-like macro each instance of a
*  parameter shall be enclosed in parentheses
*/
#define P2CONST(ptrtype, memclass, ptrclass) const ptrtype *

/**
* @brief The compiler abstraction shall define the CONSTP2VAR macro for the declaration and
*        definition of constant pointers accessing variables.
*/
/*
* @violates @ref Compiler_h_REF_1 A function should be used in
* preference to a function-like macro.
*/
/*
* @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
*    a constant, a parenthesised expression
*/
/*
* @violates @ref Compiler_h_REF_4 In the definition of a function-like macro each instance of a
*  parameter shall be enclosed in parentheses
*/
#define CONSTP2VAR(ptrtype, memclass, ptrclass) ptrtype * const

/**
* @brief The compiler abstraction shall define the CONSTP2CONST macro for the declaration and
*        definition of constant pointers accessing constants.
*/
/*
* @violates @ref Compiler_h_REF_1 A function should be used in
* preference to a function-like macro.
*/
/*
* @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
*    a constant, a parenthesised expression
*/
/*
* @violates @ref Compiler_h_REF_4 In the definition of a function-like macro each instance of a
*  parameter shall be enclosed in parentheses
*/
#define CONSTP2CONST(ptrtype, memclass, ptrclass) const ptrtype * const

/**
* @brief The compiler abstraction shall define the P2FUNC macro for the type definition of pointers
*        to functions.
*/
/*
* @violates @ref Compiler_h_REF_1 A function should be used in
* preference to a function-like macro.
*/
/*
* @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
*    a constant, a parenthesised expression
*/
/*
* @violates @ref Compiler_h_REF_4 In the definition of a function-like macro each instance of a
*  parameter shall be enclosed in parentheses
*/
#define P2FUNC(rettype, ptrclass, fctname) rettype (*fctname)

/**
* @brief The compiler abstraction shall define the CONST macro for the declaration and definition of
*        constants.
*/
/*
* @violates @ref Compiler_h_REF_1 A function should be used in
* preference to a function-like macro.
*/
/*
* @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
*    a constant, a parenthesised expression
*/
/*
* @violates @ref Compiler_h_REF_4 In the definition of a function-like macro each instance of a
*  parameter shall be enclosed in parentheses
*/
#define CONST(consttype, memclass) const consttype

/**
* @brief The compiler abstraction shall define the VAR macro for the declaration and definition of
*        variables.
*/
/*
* @violates @ref Compiler_h_REF_1 A function should be used in
* preference to a function-like macro.
*/
/*
* @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
*    a constant, a parenthesised expression
*/
/*
* @violates @ref Compiler_h_REF_4 In the definition of a function-like macro each instance of a
*  parameter shall be enclosed in parentheses
*/
#define VAR(vartype, memclass) vartype


/**
* @brief The compiler abstraction for const pointer to function.
*/
/*
* @violates @ref Compiler_h_REF_1 A function should be used in preference to a function-like macro.
* @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, a constant, a parenthesised expression
* @violates @ref Compiler_h_REF_4 In the definition of a function-like macro each instance of a parameter shall be enclosed in parentheses
*/
#define CONSTP2FUNC(rettype, ptrclass, fctname) rettype (* const fctname)


/**
* @brief The compiler abstraction shall define the FUNC_P2CONST macro for the declaration and 
* definition of functions returning a pointer to a constant
*/
/*
* @violates @ref Compiler_h_REF_1 A function should be used in preference to a function-like macro.
* @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, a constant, a parenthesised expression
* @violates @ref Compiler_h_REF_4 In the definition of a function-like macro each instance of a parameter shall be enclosed in parentheses
*/
#define FUNC_P2CONST(rettype, ptrclass, memclass) const ptrclass rettype * memclass

/**
* @brief The compiler abstraction shall define the FUNC_P2VAR macro for the declaration and 
* definition of functions returning a pointer to a variable.
*/
/*
* @violates @ref Compiler_h_REF_1 A function should be used in preference to a function-like macro.
* @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, a constant, a parenthesised expression
* @violates @ref Compiler_h_REF_4 In the definition of a function-like macro each instance of a parameter shall be enclosed in parentheses
*/
#define FUNC_P2VAR(rettype, ptrclass, memclass) ptrclass rettype * memclass

#ifdef __cplusplus
}
#endif

#endif /* #ifndef COMPILER_H */
