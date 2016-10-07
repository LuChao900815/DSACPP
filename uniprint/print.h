/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

#pragma once

#include <stdio.h> //²ÉÓÃC·ç¸ñ¾«Ï¸¿ØÖÆÊä³ö¸ñÊ½
//#include "../huffman/huffChar.h" //Huffman³¬×Ö·û
//#include "../BinTree/BinTree.h" //¶þ²æÊ÷
//#include "../Huffman/HuffTree.h" //HuffmanÊ÷
//#include "../BST/BST.h" //¶þ²æËÑË÷Ê÷
//#include "../AVL/AVL.h" //AVLÊ÷
//#include "../Splay/Splay.h" //ÉìÕ¹Ê÷
//#include "../redBlack/RedBlack.h" //ºìºÚÊ÷
//#include "../BTree/BTree.h" //¶þ²æËÑË÷Ê÷
//#include "../Entry/Entry.h" //´ÊÌõ
//#include "../Skiplist/Quadlist.h" //ËÄ²æ±í
//#include "../Skiplist/Skiplist.h" //Ìø×ª±í
//#include "../Hashtable/Hashtable.h" //É¢ÁÐ±í
//#include "../PQ_List/PQ_List.h" //»ùÓÚÁÐ±íÊµÏÖµÄÓÅÏÈ¼¶¶ÓÁÐ
//#include "../PQ_ComplHeap/PQ_ComplHeap.h" //»ùÓÚÍêÈ«¶ÑÊµÏÖµÄÓÅÏÈ¼¶¶ÓÁÐ
//#include "../PQ_LeftHeap/PQ_LeftHeap.h" //»ùÓÚ×óÊ½¶ÑÊµÏÖµÄÓÅÏÈ¼¶¶ÓÁÐ
//#include "../graph/Graph.h" //Í¼
//#include "../graphMatrix/GraphMatrix.h" //»ùÓÚÁÚ½Ó¾ØÕóÊµÏÖµÄÍ¼

/******************************************************************************************
 * Êý¾ÝÔªËØ¡¢Êý¾Ý½á¹¹Í¨ÓÃÊä³ö½Ó¿Ú
 ******************************************************************************************/
template <typename T> static void print ( T* x ) {  x ? print ( *x ) : printf ( " <NULL>" );  }
template <typename T> static void print ( T& x ) {  UniPrint::p ( x );  }
template <typename T> static void print ( const T& x ) {  UniPrint::p ( x );  } //for Stack
static void print ( char* x ) {  printf ( " %s", x ? x : "<NULL>" );  } //×Ö·û´®ÌØ±ð´¦Àí
static void print ( const char* x ) {  printf ( " %s", x ? x : "<NULL>" );  } //×Ö·û´®ÌØ±ð´¦Àí

class UniPrint {
public:
   static void p ( int );
   static void p ( float );
   static void p ( double );
   static void p ( char );
   //static void p ( HuffChar& ); //Huffman£¨³¬£©×Ö·û
   //static void p ( VStatus ); //Í¼¶¥µãµÄ×´Ì¬
   //static void p ( EType ); //Í¼±ßµÄÀàÐÍ

   //template <typename K, typename V> static void p ( Entry<K, V>& ); //Entry
   //template <typename T> static void p ( BinNode<T>& ); //BinTree½Úµã
   //template <typename T> static void p ( BinTree<T>& ); //¶þ²æÊ÷
   //template <typename T> static void p ( BTree<T>& ); //B-Ê÷
   //template <typename T> static void p ( BST<T>& ); //BST
   //template <typename T> static void p ( AVL<T>& ); //AVL
   //template <typename T> static void p ( RedBlack<T>& ); //RedBlack
   //template <typename T> static void p ( Splay<T>& ); //Splay
   //template <typename T> static void p ( Quadlist<T>& ); //Quadlist
   //template <typename K, typename V> static void p ( Skiplist<K, V>& ); //Skiplist
   //template <typename K, typename V> static void p ( Hashtable<K, V>& ); //Hashtable
   //template <typename T> static void p ( PQ_List<T>& ); //PQ_List
   //template <typename T> static void p ( PQ_ComplHeap<T>& ); //PQ_ComplHeap
   //template <typename T> static void p ( PQ_LeftHeap<T>& ); //PQ_LeftHeap
   //template <typename Tv, typename Te> static void p ( GraphMatrix<Tv, Te>& ); //Graph
   template <typename T> static void p ( T& ); //ÏòÁ¿¡¢ÁÐ±íµÈÖ§³Ötraverse()±éÀú²Ù×÷µÄÏßÐÔ½á¹¹
   //template <typename T> static void p ( T );
   template <typename T> static void p ( T* s ) //ËùÓÐÖ¸Õë
   {  s ? p ( *s ) : print ( "<NULL>" ); } //Í³Ò»×ªÎªÒýÓÃ
}; //UniPrint

/******************************************************************************************
 * 基本类型
 ******************************************************************************************/
void UniPrint::p ( int e ) { printf ( " %04d", e ); }
void UniPrint::p ( float e ) { printf ( " %4.1f", e ); }
void UniPrint::p ( double e ) { printf ( " %4.1f", e ); }
void UniPrint::p ( char e ) { printf ( " %c", ( 31 < e ) && ( e < 128 ) ? e : '$' ); }
//void UniPrint::p ( VStatus e ) {
//   switch ( e ) {
//      case UNDISCOVERED:   printf ( "U" ); break;
//      case DISCOVERED:     printf ( "D" ); break;
//      case VISITED:        printf ( "V" ); break;
//      default:             printf ( "X" ); break;
//   }
//}
//void UniPrint::p ( EType e ) {
//   switch ( e ) {
//      case UNDETERMINED:   printf ( "U" ); break;
//      case TREE:           printf ( "T" ); break;
//      case CROSS:          printf ( "C" ); break;
//      case BACKWARD:       printf ( "B" ); break;
//      case FORWARD:        printf ( "F" ); break;
//      default:             printf ( "X" ); break;
//   }
//}

#include "print_implementation.h"