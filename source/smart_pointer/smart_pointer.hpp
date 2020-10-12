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
 * Alumna: Andrea Cecilia Vargas Andia
 * Curso: Estructuras de Datos Avanzadas
 * Grupo: CCOMP6-1
 *
 *Referencias:
 *https://codereview.stackexchange.com/questions/25214/reference-counting-smart-pointer-class
 *https://www.acodersjourney.com/implementing-smart-pointer-using-reference-counting/
 *https://www.go4expert.com/articles/smart-pointer-reference-counting-t16448/
 *https://stackoverflow.com/questions/725142/how-does-a-reference-counting-smart-pointers-reference-counting-work
*/
template <typename Type>
class SmartPointer {
 private:
  Type *resource_;
  size_t *ref_count;
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
  explicit SmartPointer(Type *resource) :resource_(resource)
  {
      ref_count= new size_t(1) ;
  }

  SmartPointer() :resource_(nullptr),ref_count(nullptr){}

  /* Destructor: ~SmartPointer();
   * Uso: (implícito)
   * ------------------------------------------------------------
   * Decrementa el contador de referencias del recurso, eliminando
   * y liberando la memoria si fuera el último SmartPointer apuntando
   * al recurso.
   */
  ~SmartPointer()
  {
      if (ref_count)
      {
          --(*ref_count);
          if (!(*ref_count))
          {
              delete resource_;
              delete ref_count;
          }
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
/*---SmartPointer &operator=(const SmartPointer &other) { return *this; }
  SmartPointer &operator=(Type *other) { return *this; }
  SmartPointer(const SmartPointer &other) {}*/

  SmartPointer &operator=(const SmartPointer &other)
    {
        if (&other != this)
        {
            Detach();
            resource_=other.GetPointer;
            ref_count=other.GetReferenceCount;
            ++ref_count;
        }
            
        return *this;
    }
   SmartPointer &operator=(Type *other)
   {  
       if (resource_ != other) {
          Detach();
          resource_ = other;
          ref_count = new size_t(1);
      }

    return *this;
   }
   SmartPointer(const SmartPointer &other) 
   {
       ref_count=other.ref_count;
       resource_=other.GetPointer();
       ++(*ref_count);
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
  size_t* GetReferenceCount() const { return *ref_count; }

  /* Helper Function: se des-asocia del recurso;
   * Uso: ptr.Detach();
   * ------------------------------------------------------------
   * Deja de administrar un recurso. eliminando y liberando la
   * memoria si es necesario.
   */
  void Detach()
  {
      if (ref_count)
      {
          --(*ref_count);
          if (!(*ref_count))
          {
              delete resource_;
              delete ref_count;
              resource_=nullptr;
              ref_count=nullptr;
          }
       }
       
  }
};


#endif  // SOURCE_SMART_POINTER_SMART_POINTER_HPP_
