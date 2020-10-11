// Copyright 2020 Roger Peralta Aranibar
#ifndef SOURCE_SMART_POINTER_SMART_POINTER_HPP_
#define SOURCE_SMART_POINTER_SMART_POINTER_HPP_
#include <cstddef>
#include <iostream>
using namespace std;

/*
 * Smart Pointer que implementa un tipo de estrategia por conteo de referencias.
 * Permite que varios SmartPointers puedan acceder al mismo recurso compartido.
 * Cuando el ˙ltimo puntero es eliminado, se elimina y libera el recurso.
 */

//EL RECURSO COMPARTIDO DEBE DE SER GENERAL PARA TODOS LOS RECURSOS Y DEBE DE ACTUAR COMO UN CONTROLADOR, SI LO CREO COMO UN PUNTERO A UNA CLASE
//TODOS LOS PUNTEROS QUE APUNTEN A ESE RECURSO TENDRAN LA MISMA Y UNICA CLASE.

class contador
{
  public:
   int cont;
   contador() {cont = 1;}
};



template <typename Type>
class SmartPointer {
 private:
  Type *resource_;
  contador *conta;
  

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
    //NOS FACILITAMOS CON EL CONTRUCTOR DE CONTADOR CLASS, PORQUE YA SABEMOS QUE ESTAMOS APUNTANDO A UN NUEVO RECURSO +1
     conta = new contador();
     //cout << conta->cont << '\n';
     resource_ = resource;

  }
  explicit SmartPointer()
  {
    //NOS FACILITAMOS CON EL CONTRUCTOR DE CONTADOR CLASS, PORQUE YA SABEMOS QUE ESTAMOS APUNTANDO A UN NUEVO RECURSO NULO +1
    conta = new contador();
    resource_(nullptr);
  } 

  /* Destructor: ~SmartPointer();
   * Uso: (implícito)
   * ------------------------------------------------------------
   * Decrementa el contador de referencias del recurso, eliminando
   * y liberando la memoria si fuera el último SmartPointer apuntando
   * al recurso.
   */
  
  ~SmartPointer() 
  {
    /*cout << "ENTRE AL DESTRUCTOR" << '\n';
    cout << conta->cont << '\n';
    RESTAMOS UNO AL COTNADOR GENERAL PORQUE ESTAMOS DESVINCULANDO UN SMART POINTER DE ESE RECURSO SI ES CERO ENTONCES LO ELIMINAMOS
    */
    deletes();
    if(conta->cont == 0)
    {
      delete resource_;
      delete conta;
    }
  }

  void add()
  {
    //INCREMENTAR
      ++conta->cont;
  }
  void deletes()
  {
    //DECREMENTAR
      --conta->cont;
  }
  /*
SmartPointer operadores de "des-referencia"(dereference)
   * Uso: cout << *myPtr << endl;
   * Uso: cout << myPtr->length << endl;
   * ------------------------------------------------------------
   * Permite al SmartPointer comportarse como si fuera un puntero.
   */
  Type &operator*() const 
  {
     return Type(0);    
  }
  Type *operator->() const 
  {
     return Type; 
  }

  /* Funciones de copia
   * Uso: SmartPointer<string> ptr=existingPointer;
   *      ptr=existingPtr;
   * ------------------------------------------------------------
   * Cambia el recurso referenciado por este SmartPointer por otro
   * SmartPointer. Si el conteo llega a cero, debe ser eliminado
   * (deallocated).
   */

  SmartPointer &operator=(const SmartPointer &other)
   { //EVITAR QUE EL PUNTERO SE APUNTE A SI MISMO
     if (this != &other)
     {
      //ES PARA VERIFICAR SI SOLO HAY UN RECURSO EN NUESTRO ANTIGUO SMARTPOINTER, REDUCIENDO EL CONTADOR DEL ANTIGUO RECURSO SI SOLO HABIA UN SMART ENTONCES LO BORRAMOS
        deletes();
        if(conta->cont == 0)
        {
          delete resource_;
          delete conta;
        }
        /*else
        {
          deletes();
        }*/
      

      //NUESTROS RECURSO Y NUESTRO CONTADOR LO TOMAREMOS DE LA NUEVA CLASE Y SUMAMOS +1  PORQUE SERA UN SMARTPOINTER MÁS HACIA ESE RECURSO
      resource_ = other.GetPointer();
      conta = other.conta;
      add();
     }

     /*cout << "COMPROBANDO" << '\n';
     cout << conta->cont << '\n';*/
     return *this; 
   }

  SmartPointer &operator=(Type *other) { 
          
          //ESTO ES PARA EL DETACH PARA QUE NO ENTRE, PORQUE SE BORRIA LA NADA A LA QUE ESTA APUNTANDO, SI FUESE EL DETACH SOLO CREAMOS UN NUECO CONTADOR Y 
          //QUE APUNTE AL NUEVO RECURSO
          if(!conta->cont == 0)
          {
              deletes();
              if(conta->cont == 0)
              {
                delete conta;
                delete resource_;
              }
          }

           conta = new contador();
          resource_ = other;
          //cout << "COMPROBANDO2" << '\n';
          return *this;
    }

  SmartPointer(const SmartPointer &other) 
  {
      //cout << "COMPROBANDO3" << '\n';
      //EVITAR QUE EL PUNTERO SE APUNTE A SI MISMO
      if (this != &other)
     {
       //SOLO IGUALAMOS A LOS NUEVOS RECURSOS
        resource_ = other.GetPointer();
        conta = other.conta;
        add();
     }
     //cout << conta->cont << '\n';  
  }

  /* Helper Function: Obtener recurso.
   * Uso: Type* p=GetPointer();
   * ------------------------------------------------------------
   * Retorna una variable puntero al recurso administrado.
   */
  Type *GetPointer() const { return resource_;}

  /* Helper Function: Obtiene conteo
   * Uso: if (ptr.GetReferenceCount()==1) // Única referencia
   * ------------------------------------------------------------
   * Retorna el número de referencias apuntando al recurso.
   */
  size_t GetReferenceCount() const { return conta->cont; }


  /* Helper Function: se des-asocia del recurso;
   * Uso: ptr.Detach();
   * ------------------------------------------------------------
   * Deja de administrar un recurso. eliminando y liberando la
   * memoria si es necesario.
   */

  void Detach() 
  {
    //ES PARA NO CREAR NUEVAS INSTANCIAS CREO Y ELIMINO PARA QUE NO APUNTEN A NINGUN LADO
    deletes();
    if (conta->cont == 0)
    {
      delete resource_;
      delete conta;
    }
    else
    {
      conta = new contador();
      delete conta;
      resource_ = new Type;
      delete resource_;
    }
    
  }
};

#endif  // SOURCE_SMART_POINTER_SMART_POINTER_HPP_
