#include<stdio.h>
#include<malloc.h>
#include<memory.h>

typedef struct ringBuff{
    int * buff;
    int start;
    int end;
    int size;
    int count;
} ringBufft;

ringBufft * ringBuff_new(int size)
{
  ringBufft * cb = (ringBufft*)malloc(sizeof(ringBufft));
  memset(cb, 0, sizeof(ringBufft));
  cb->size = size;
    cb->buff = (int*)malloc(sizeof(int)*size);

  return cb;
}

void ringBuff_add(ringBufft * cb, int elem)
{
  int end = cb->end;
  if(cb->count && (end % cb->size) == cb->start){
    printf("\nThe buffer is full, the element [%d] %d has been replaced.\n", cb->start, cb->buff[cb->start]);
    cb->start = (cb->start + 1 ) %cb->size;
    cb->count --;
  }

  printf("\nAdded Elem[%d] = %d\n",cb->end, elem);
  cb->buff[cb->end] = elem;
  cb->end = (cb->end+1) % cb->size;
  cb->count ++;
  }

int ringBuff_remove(ringBufft * cb)
{
  int start = cb->start ;
  int ret = -1;
  if(cb->count <= 0) {
    printf("Buffer is empty\n");
    return ret;
  }
  if(cb->count || (start % cb->size) != cb->end) {
    printf("Removed Elem[%d] = %d\n",cb->start, cb->buff[cb->start]);
    ret = cb->buff[cb->start];
    cb->start = (cb->start + 1 ) % cb->size;
    cb->count--;
  } else {
    printf("Buffer is empty\n");
  }
  return ret;
}

void ringBuff_print(ringBufft * cb)
{
  int start = cb->start ;
  int end = cb->end ;
  int i, count = 0;
  for(i = start; count < cb->count; i = (i + 1)%cb->size){
    printf("Elem[%d] = %d\n", i, cb->buff[i]);
    count++;
    if(i == (end - 1)) {
      break;
    }
  }
}

void ringBuff_delete(ringBufft * cb)
{
  free(cb->buff);
  free(cb);
}

int main(int argc, char *argv[])
{
  char key;
  int elem;
  int size;

  printf("Enter the buffer size\n\n > ");

  scanf("%d", &size);

  ringBufft * cb = ringBuff_new(size);

  while(1) {
    printf("\nRing buffer\n1. add\n2. remove\n3. print\n4. Create new buffer\n\n > ");
    fflush(stdin);
    key = getchar();
    printf("\n");
    switch(key){
      case '1':
      {
        printf("Element to add : ");
        scanf("%d", &elem);
        ringBuff_add(cb, elem);
        break;
      }
      case '2':
      {
        ringBuff_remove(cb);
        break;
      }
      case '3':
      {
        ringBuff_print(cb);
        break;
      }
      case '4':
      {
        ringBuff_delete(cb);

        printf("Enter the buffer size\n\n > ");

        scanf("%d", &size);

        ringBufft * cb = ringBuff_new(size);

        break;
      }
      default:
      {
        ringBuff_delete(cb);
      }
    }
  }
  return 0;
}
