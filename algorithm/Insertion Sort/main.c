#include <stdio.h>
#include <stdlib.h>
#define LENGTH 100000

void print(int a[], int length);

// ascending sort using insertion sort
// I finish this shit with a theta(n) = n^5, so fuck me, I'm a idiot
void insertion_sort_bad(int a[],int length){
    // loop from the 2nd element, to the end
    // maker: n -> n
    for(int i = 1; i < length; i++){
        // we define the current i element as key
        int key = a[i];
        // loop from 1th lement to the element before the key
        // compare key and current  j element
        // dicdie what gona do depends on the comparing result
        // maker: {1...(n-1)} -> n^2
        for(int j = 0; j < i; j++){
            // if the key is smaller than or equal to  the current j element, skipping
            if(a[j] <= key) continue;
            else{
                // if the key is larger, move the element bind j element (including j element) to the next one position
                // maker: {1 ... (n-1)} -> n^2
                for(int k = i; k  > j; k--)
                    a[k] = a[k-1];
                // insert  the key to the current j position.
                a[j] = key;
                break;
            }
        }
    }
}

// using while to write a real insertion_sort
void insertion_sort(int a[],int length){
    for(int j = 1; j < length; j++)
    {
        int key = a[j];
        int i = j-1;
        while(i >= 0 && a[i] > key){
            a[i+1] = a[i];
            i--;
        }
        a[i+1] = key;
        // break;
        // print(a,LENGTH);
    }
    return;
}


void print(int a[], int length){
    for(int i = 0; i < length; i++){
        printf("%d ", a[i]);
    }
    printf("\n");
    return;
}

int* generate(int length){
    int *a = malloc(length*sizeof(int));
    for(int i = 0; i < length; i++){
        a[i] = length - i;
    }
    return a;
}
int main(){
    int* a = generate(LENGTH);
    // print(a,LENGTH);
    insertion_sort(a,LENGTH);
    // print(a,LENGTH);kk
    free(a);
}