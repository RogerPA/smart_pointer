// Copyright 2020 Roger Peralta Aranibar
#ifndef SOURCE_SMART_POINTER_SMART_POINTER_HPP_
#define SOURCE_SMART_POINTER_SMART_POINTER_HPP_
#include <cstddef>

/*
 * Smart Pointer que implementa un tipo de estrategia por conteo de referencias.
 * Permite que varios SmartPtrs puedan acceder al mismo recurso compartido.
 * Cuando el ˙ltimo puntero es eliminado, se elimina y libera el recurso.
 */
template <typename Type>
class SmartPointer {
 public:
  /* Constructor: SmartPointer(Type* resource = NULL)
   * Uso: SmartPointer<string> my_ptr(new string);
   *      SmartPointer<string> my_ptr;
   * ------------------------------------------------------------
   * Construye un nuevo objeto SmartPointer que administra el recurso
   * asignado. Se asume que el recurso viene de una llamada a new.
   * El recurso tambiÈn podrÌa ser NULL lo que ocasionarÌa que el
   * recurso no administre ning˙n recurso.
   */
  explicit SmartPointer(Type* resource = nullptr);

  /* Destructor: ~SmartPointer();
   * Uso: (implÌcito)
   * ------------------------------------------------------------
   * Decrementa el contador de referencias del recurso, eliminando
   * y liberando la memoria si fuera el ˙ltimo SmartPointer apuntando
   * al recurso.
   */
  ~SmartPointer();

  /* SmartPointer operadores de "de-referencia"(dereference)
   * Uso: cout << *my_ptr << endl;
   * Uso: cout << my_ptr->length << endl;
   * ------------------------------------------------------------
   * Permite al SmartPointer comportarse como si fuera un puntero.
   */
  Type& operator*() const;
  Type* operator->() const;

  /* Funciones de copia
   * Uso: SmartPointer<string> ptr = existing_pointer;
   *      ptr = existing_ptr;
   * ------------------------------------------------------------
   * Cambia el recurso referenciado por este SmartPointer por otro
   * SmartPointer. Si el conteo llega a cero, debe ser eliminado
   * (deallocated).
   */
  SmartPointer& operator=(const SmartPointer& other);
  SmartPointer& operator=(Type* other);
  SmartPointer(const SmartPointer& other);

  /* Helper Function: Obtener recurso.
   * Uso: Type* p = GetPointer();
   * ------------------------------------------------------------
   * Retorna una variable puntero al recurso administrado.
   */
  Type* GetPointer() const;

  /* Helper Function: Obtiene conteo
   * Uso: if (ptr.GetReferenceCount() == 1) // ⁄nica referencia
   * ------------------------------------------------------------
   * Retorna el n˙mero de referencias apuntando al recurso.
   */
  size_t GetReferenceCount() const;

  /* Helper Function: se des-asocia del recurso;
   * Uso: ptr.Detach();
   * ------------------------------------------------------------
   * Deja de administrar un recurso. eliminando y liberando la
   * memoria si es necesario.
   */
  void Detach();
};
#endif  // SOURCE_SMART_POINTER_SMART_POINTER_HPP_
