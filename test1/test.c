#include <stdio.h>
#include <stdlib.h>

//--------------------------------------
// API, ����������� ���������� ������
// � ��� �������� � ���
// ������ ����������� ���������� �� ������ ����
// ���� ��������� � ��������� �������

typedef
  struct ListNode {
      struct ListNode *next;
      struct ListNode *prev;
      void *data;
  } ListNode;

  // ����������� ��� ���� ������ � ��� ��������� � ���� ������
  // O(n)
  void listFree(ListNode** list) { //
      if(!*list)
          return;
      ListNode* curNode = *list;
      do {
          free(curNode->data); //�� ��������� data �� NULL, �.�. free(NULL) ��������� � ��������� C
          ListNode* next = curNode->next;
          free(curNode);
          curNode = next;
      } while(curNode != *list); //����������� �� ���������� ��������� ����
      *list = NULL;
  }

  // ���������� true, ���� ������ ����
  // O(1)
  char listEmpty(ListNode** list) {
      return(!*list);  //������ ����, ���� �� �� �������� �����
  }

  // ���������� ��������� ���� ������
  // O(1)
  ListNode* listBack(ListNode** list) {
      if(!*list)
          return NULL;
      return (*list)->prev;
  }

  // ���������� ������ ���� ������
  // O(1)
  ListNode* listFront(ListNode** list) {
      return *list;
  }

  // ������� ���� p �� ������, ���������� ��������� �� ��������� ����
  // ������� ��������� ������
  // O(1)
  ListNode* listErase(ListNode** list, ListNode* node) {
      if(!node)
          return NULL;
      free(node->data);
      node->prev->next = node->next;
      node->next->prev = node->prev;
      ListNode* next = node->next;
      if(node == *list)
          *list = next;
      free(node);
      return next;
  }

  // ������� ���� �� ������, ������ � from, ���������� to (������������),
  // ���������� ��������� �� ��������� �� to ����
  // ������� ��������� ������
  // O(n)
  ListNode* listEraseRange(ListNode** list, ListNode* from, ListNode* to) {
      ListNode* next = (to->next != from)? to->next: NULL;
      ListNode* p = from;
      do {
          p = listErase(list, p);
      } while (p != next);
      return next;
  }

  //������ ����� ���� ����� ��������, ���������� ��������� �� ����
  // O(1)
  ListNode* listInsert(ListNode* node) {
      ListNode* newnode = malloc(1);
      ListNode* prev = node->prev;
      node->prev->next = newnode;
      node->prev = newnode;
      newnode->next = node;
      newnode->prev = prev;
      return newnode;
  }

  //��������� ���� � ����� ������, ���������� ��������� �� ����
  //O(1)
  ListNode* listPushBack(ListNode** list) {
      if(*list)
          return listInsert(*list);
      //���� ������ ����, ������ ����� ������
      ListNode* ln = malloc(1);
      ln->next = ln->prev = ln;
      ln->data = NULL;
      *list = ln;
      return *list;
  }

  //��������� ���� � ������ ������, ���������� ��������� �� ����

  //O(1)
  ListNode* listPushFront(ListNode** list) {
      if(*list) {
          *list = listInsert(*list);
          return *list;
      }
      //���� ������ ����, ������ ����� ������
      ListNode* ln = malloc(1);
      ln->next = ln->prev = ln;
      ln->data = NULL;
      *list = ln;
      return *list;
  }

  //������� ���� � ����� ������, ���������� ��������� �� ����
  //O(1)
 void listPopBack(ListNode** list) {
     listErase(list, (*list)->prev);
  }

 //������� ���� � ������ ������, ���������� ��������� �� ��������� ����
 //O(1)
ListNode* listPopFront(ListNode** list) {
    *list = listErase(list, *list);
    return *list;
 }

 //���������� ������ ������
size_t listSize(ListNode** list) {
  if(!list)
      return 0;
  size_t i = 0;
  ListNode* begin = *list;
  ListNode* cur = *list;
  do {
      ++i;
      cur = cur->next;
  }
  while(cur != begin);
  return i;
}

//�������� ������ ������ �� N. ���� N ������ �������� ������� S, ������� � ����� S - N �����,
//���� N > S, ��������� � ����� N - S �����
//O(n)
void listResize(ListNode** list, size_t n) {
    size_t s = listSize(list);
    if(s <= n) {
        for(size_t i = 0; i < n - s; ++i) {
            listPushBack(list);
        }
    } else {
        for(size_t i = 0; i < s - n; ++i) {
            listPopBack(list);
        }
    }
}

// ���������� ����, n-�� �� ��������
//O(n)
ListNode* listNext(ListNode* node, size_t n) {
    ListNode* result = node;
    for(size_t i = 0; i < n; ++i)
        result = result->next;
    return result;
}

// ���������� ����, n-�� �� �������� � �������� �����������
//O(n)
ListNode* listPrev(ListNode* node, size_t n) {
    ListNode* result = node;
    for(size_t i = 0; i < n; ++i)
        result = result->prev;
    return result;
}
//------------------------
// test function
typedef
  struct {
      int id;
      int arr[100];
  } ListData;

  ListData* allocData(int id) {
      ListData* data = malloc(1);
      data->id = id;
      return data;
  }

  int getId(ListData* data) {
      return data->id;
  }

int main(void)
{
    ListNode* testList = NULL;
    ListNode* node = listPushBack(&testList);
    node->data = allocData(1);
    printf("test 1\nsize = %u, last id = %i\n", listSize(&testList), getId(listBack(&testList)->data));
    //--------
    for(int i = 0; i < 100; ++i) {
        node = listPushBack(&testList); //->data = allocData(i);
        node->data = allocData(i);
    }
    printf("test 2\nsize = %u, last id = %i\n", listSize(&testList), getId(listBack(&testList)->data));
    //--------
    for(int i = 0; i < 100; ++i) {
        node = listPushFront(&testList);
        node->data = allocData(i);
    }
    printf("test 3\nsize = %u, first id = %i\n", listSize(&testList), getId(listFront(&testList)->data));
    //--------
    for(int i = 0; i < 100; ++i) {
        node = listInsert(listNext(&testList, 50));
        node->data = allocData(i);
    }
    printf("test 4\nsize = %u, id(100) = %i\n", listSize(&testList), getId(listNext(&testList, 100)->data));
    //--------
    listFree(&testList);
    if(listEmpty(&testList))
        printf("test4: list empty\n");
    //--------
    for(int i = 0; i < 100; ++i) {
        node = listPushFront(&testList);
        node->data = allocData(i);
    }
    listErase(&testList, listFront(&testList));
    printf("test 5\nsize = %u, id(0) = %i\n", listSize(&testList), getId(listFront(&testList)->data));
    listErase(&testList, listFront(&testList));
    //--------------
    listEraseRange(&testList, listNext(testList, 10), listNext(testList, 20));
    node = testList;
    for(int i = 0; i < 30; ++i) {
        printf("id(%d) = %d\n", i, ((ListData*)(node->data))->id);
        node = node->next;
    }
    printf("test 6\nsize = %u, id(10) = %i\n", listSize(&testList), getId(listFront(&testList)->data));
    //--------------
    listPopBack(&testList);
    printf("test 7\nsize = %u, id(back) = %i\n", listSize(&testList), getId(listBack(&testList)->data));
    //--------------
    listPopFront(&testList);
    printf("test 8\nsize = %u, id(front) = %i\n", listSize(&testList), getId(listFront(&testList)->data));
    //--------------
    listResize(&testList, 10);
    printf("test 9\nsize = %u, id(back) = %i\n", listSize(&testList), getId(listBack(&testList)->data));
    //--------------
    listResize(&testList, 20);
    node = testList;
    for(int i = 0; i < 20; ++i) {
        node->data = allocData(i);
        node = node->next;
    }
    printf("test 10\nsize = %u, id(back) = %i\n", listSize(&testList), getId(listBack(&testList)->data));
    return 0;
}
