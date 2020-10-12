// Copyright 2020 Roger Peralta Aranibar
#ifndef SOURCE_SMART_POINTER_SMART_POINTER_HPP_
#define SOURCE_SMART_POINTER_SMART_POINTER_HPP_
#include <cstddef>

/*
 * Smart Pointer que implementa un tipo de estrategia por conteo de referencias.
 * Permite que varios SmartPointers puedan acceder al mismo recurso compartido.
 * Cuando el ˙ltimo puntero es eliminado, se elimina y libera el recurso.
 */

/*
 * Toda la información del Smart Pointer es referenciada de: 
 * https://www.geeksforgeeks.org/smart-pointers-cpp/
 * https://docs.microsoft.com/en-us/cpp/cpp/smart-pointers-modern-cpp?view=vs-2019
 *
 * Nombre del Alumno: Patrick Xavier Márquez Choque
 * Código implementado haciendo un fork del Repositorio del Profesor Roger Peralta.
 * Curso: Estructuras de Datos Avanzadas (Laboratorio)
 * Periodo: 2020-2
 */

template <typename Type>
class SmartPointer {
 private:
  Type *resource_;
  size_t *ptr

 public:
  /* Constructor: SmartPointer(Type* resource=NULL)
   * Uso: SmartPointer<string> myPtr(new string);
   *      SmartPointer<string> myPtr;
   * ------------------------------------------------------------
   * Construye un nuevo objeto SmartPointer que administra el recurso
   * asignado. Se asume que el recurso viene de una llamada a new.
   * El recurso también podría ser NULL lo que ocasionaría que el
   * recurso no administre ningún recurso.
   */
  explicit SmartPointer(Type *resource) : resource_(resource) {}
  explicit SmartPointer(Type *resource = nullptr){
   resource_ = resource;
   if(resource_){ ptr = new size_t(1); }
   else{ ptr = nullptr; }   
  }

  /* Destructor: ~SmartPointer();
   * Uso: (implícito)
   * ------------------------------------------------------------
   * Decrementa el contador de referencias del recurso, eliminando
   * y liberando la memoria si fuera el último SmartPointer apuntando
   * al recurso.
   */
  ~SmartPointer() { Detach(); }

  /* SmartPointer operadores de "des-referencia"(dereference)
   * Uso: cout << *myPtr << endl;
   * Uso: cout << myPtr->length << endl;
   * ------------------------------------------------------------
   * Permite al SmartPointer comportarse como si fuera un puntero.
   */
  Type &operator*() const { return Type(0); }
  Type *operator->() const { return nullptr; }
  Type &operator*() const { return *ptr; }
  Type *operator->() const { return ptr; }

  /* Funciones de copia
   * Uso: SmartPointer<string> ptr=existingPointer;
   *      ptr=existingPtr;
   * ------------------------------------------------------------
   * Cambia el recurso referenciado por este SmartPointer por otro
   * SmartPointer. Si el conteo llega a cero, debe ser eliminado
   * (deallocated).
   */
  SmartPointer &operator=(const SmartPointer &other) { return *this; }
  SmartPointer &operator=(Type *other) { return *this; }
  SmartPointer(const SmartPointer &other) {}
  SmartPointer &operator=(const SmartPointer &other) {
   if(resource_ && resource_ == other.GetPointer()) { return *this; }
   Detach();
   resource_ = other.GetPointer();
   ptr = other.GetReferenceCount();
   (*ptr)++;
   return *this;
  }
  SmartPointer &operator=(Type &other){
   resource_ = other.GetPointer();
   ///ptr = &(other.GetReferenceCount());
   ptr = other.GetCount();
   (*ptr)++;
   return *this;
  }
  SmartPointer &operator=(Type *other){
   if(resource_ && resource_ == other.GetPointer()) { return *this; }
   Detach();
   resource_ = other;
   ptr = new size_t(1);
   (*ptr)++;
   return *this;
  }

  /* Helper Function: Obtener recurso.
   * Uso: Type* p=GetPointer();
   * ------------------------------------------------------------
   * Retorna una variable puntero al recurso administrado.
   */
  Type *GetPointer() const { return nullptr; }
  Type *GetPointer() const { return resource_; }

  /* Helper Function: Obtiene conteo
   * Uso: if (ptr.GetReferenceCount()==1) // Única referencia
   * ------------------------------------------------------------
   * Retorna el número de referencias apuntando al recurso.
   */
  size_t GetReferenceCount() const { return 0; }
  size_t GetReferenceCount() const { return *ptr; }
  size_t* GetCount() const { return ptr; }

  /* Helper Function: se des-asocia del recurso;
   * Uso: ptr.Detach();
   * ------------------------------------------------------------
   * Deja de administrar un recurso. eliminando y liberando la
   * memoria si es necesario.
   */
  void Detach() {
   if(resource_ && (*ptr)-- == 0){
    delete resource_;
    delete ptr;
    resource_ = nullptr;
    ptr = nullptr;
   }
  }
};

#endif  // SOURCE_SMART_POINTER_SMART_POINTER_HPP_
