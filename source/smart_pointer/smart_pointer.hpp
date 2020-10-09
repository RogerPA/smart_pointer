// Copyright 2020 Roger Peralta Aranibar
#ifndef SOURCE_SMART_POINTER_SMART_POINTER_HPP_
#define SOURCE_SMART_POINTER_SMART_POINTER_HPP_
#include <cstddef>
#include <map>
/*
 * Smart Pointer que implementa un tipo de estrategia por conteo de referencias.
 * Permite que varios SmartPointers puedan acceder al mismo recurso compartido.
 * Cuando el ˙ltimo puntero es eliminado, se elimina y libera el recurso.
 */
template <typename Type>
class SmartPointer
{
private:
  Type *resource_;
  static std::map<Type *, int> table_pointers; // uso map para tener una tabla de registros de punteros
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
  explicit SmartPointer(Type *resource)
  {
    if (resource != nullptr)
    {
      resource_ = resource;
      table_pointers[resource_]++;
    }
  }

  explicit SmartPointer() {}

  /* Destructor: ~SmartPointer();
   * Uso: (implícito)
   * ------------------------------------------------------------
   * Decrementa el contador de referencias del recurso, eliminando
   * y liberando la memoria si fuera el último SmartPointer apuntando
   * al recurso.
   */
  ~SmartPointer()
  {
    if (resource_ != nullptr) // para que eliminar si es nulo
    {
      Detach();
    }
  }

  /* SmartPointer operadores de "des-referencia"(dereference)
   * Uso: cout << *myPtr << endl;
   * Uso: cout << myPtr->length << endl;
   * ------------------------------------------------------------
   * Permite al SmartPointer comportarse como si fuera un puntero.
   */
  Type &operator*() const { return *resource_; }
  Type *operator->() const { return resource_; }

  /* Funciones de copia
   * Uso: SmartPointer<string> ptr=existingPointer;
   *      ptr=existingPtr;
   * ------------------------------------------------------------
   * Cambia el recurso referenciado por este SmartPointer por otro
   * SmartPointer. Si el conteo llega a cero, debe ser eliminado
   * (deallocated).
   */
  SmartPointer &operator=(const SmartPointer &other)
  {
    if (resource_ != other.resource_) // si el puntero es distinto tiene sentido
    {
      if (other.resource_ != nullptr) // creamos otro registro en tabla, o aumentamos el que tenemos
        table_pointers[other.resource_]++;
      if (resource_ != nullptr) // decrementamos nuestro registro actual
        Detach();
      resource_ = other.resource_;
    }
    return *this;
  }
  SmartPointer &operator=(Type *other)
  {
    if (resource_ != nullptr) // decrementamos el registro actual si apuntamos a algo no nulo
      Detach();
    if (other != nullptr) // creamos otro registro en tabla, o aumentamos el que tenemos
      table_pointers[other]++;
    resource_ = other;
    return *this;
  }
  SmartPointer(const SmartPointer &other)
  {
    if (other.resource_ != nullptr)
    {
      table_pointers[other.resource_]++;
      resource_ = other.resource_;
    }
  }

  /* Helper Function: Obtener recurso.
   * Uso: Type* p=GetPointer();
   * ------------------------------------------------------------
   * Retorna una variable puntero al recurso administrado.
   */
  Type *GetPointer() const { return resource_; }

  /* Helper Function: Obtiene conteo
   * Uso: if (ptr.GetReferenceCount()==1) // Única referencia
   * ------------------------------------------------------------
   * Retorna el número de referencias apuntando al recurso.
   */
  size_t GetReferenceCount() const { return table_pointers[resource_]; } // solo retornamos el contador de punteros al recurso

  /* Helper Function: se des-asocia del recurso;
   * Uso: ptr.Detach();
   * ------------------------------------------------------------
   * Deja de administrar un recurso. eliminando y liberando la
   * memoria si es necesario.
   */
  void Detach()
  {
    --table_pointers[resource_];
    if (!table_pointers[resource_]) // si el contador llega a 0
    {
      Type *temp = nullptr;
      temp = resource_;
      table_pointers.erase(resource_); // eliminamos el registro del puntero de la tabla
      delete temp;
    }
    resource_ = nullptr;
  }
};
template <class T>
std::map<T *, int> SmartPointer<T>::table_pointers;
#endif // SOURCE_SMART_POINTER_SMART_POINTER_HPP_
