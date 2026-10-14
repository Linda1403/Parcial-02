// =====================================================================
//  main.cpp -- PLANTILLA. Unico lugar donde se usa cin/cout.
//  Protocolo de entrada/salida: ver anexo_enunciado.md
//    1) Pedir correo y contrasena (cin >> ...). Si iniciarSesion falla -> imprimir
//       "Usuario invalido" y terminar.
//    2) Menu en ciclo hasta elegir 0:
//       1 Listar productos (stock < 15)      4 Adicionar producto al carrito (pide id)
//       2 Comentarios desde una fecha (pide fecha dd/mm/yyyy)   5 Listar productos del carrito
//       3 Listar usuarios                    0 Salir
// =====================================================================
#include <iostream>
#include <string>
#include <vector>

#include "plataforma.h"

using namespace std;

int main() {
    vector<Usuario> usuarios = cargarUsuarios();
    vector<Producto> productos = cargarProductos();
    vector<Comentario> comentarios = cargarComentarios();
    vector<CarritoDeCompras> carritos;

    string correo, contrasena;
    if (!(cin >> correo >> contrasena)) {
        cout << "Usuario invalido" << endl;
        return 0;
    }

    Usuario usuarioLogueado;
    if (!iniciarSesion(usuarios, correo, contrasena, usuarioLogueado)) {
        cout << "Usuario invalido" << endl;
        return 0;
    }

    int opcion;
    while (cin >> opcion) {
        if (opcion == 0) {
            break;
        }

        if (opcion == 1) {
            vector<Producto> bajoStock = productosBajoStock(productos, 15);
            for (const auto& p : bajoStock) {
                cout << p.idProducto << " - " << p.nombre << " | Stock: " << p.stock << " | Precio: " << p.precio << endl;
            }
        } else if (opcion == 2) {
            string fecha;
            if (cin >> fecha) {
                vector<Comentario> coms = comentariosDesde(comentarios, fecha);
                for (const auto& c : coms) {
                    cout << c.idComentario << " | " << c.usuario << " | " << c.producto << " | " << c.fecha << " | " << c.comentario << endl;
                }
            }
        } else if (opcion == 3) {
            vector<string> uFormateados = listarUsuariosFormateados(usuarios);
            for (const auto& line : uFormateados) {
                cout << line << endl;
            }
        } else if (opcion == 4) {
            int idProd;
            if (cin >> idProd) {
                agregarAlCarrito(carritos, productos, usuarioLogueado, idProd);
            }
        } else if (opcion == 5) {
            int idCarritoUsuario = -1;
            for (const auto& c : carritos) {
                if (c.usuario.idUsuario == usuarioLogueado.idUsuario) {
                    idCarritoUsuario = c.idCarrito;
                    cout << "Subtotal: " << c.subtotal << " | Impuestos: " << c.impuestos << endl;
                    break;
                }
            }

            if (idCarritoUsuario != -1) {
                vector<Producto> prodsCarrito = listarProductosCarrito(carritos, idCarritoUsuario);
                for (const auto& p : prodsCarrito) {
                    cout << p.idProducto << " - " << p.nombre << " | Precio: " << p.precio << endl;
                }
            }
        }
    }

    return 0;
}
