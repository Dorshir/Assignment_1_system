#include "AdptArray.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct AdptArray_ {
    int arrSize;
    PElement *elemArr;
    DEL_FUNC delFunction;
    COPY_FUNC copyFunction;
    PRINT_FUNC printFunction;

} AdptArray, *PAdptArray;

PAdptArray CreateAdptArray(COPY_FUNC copyFunc, DEL_FUNC delFunc, PRINT_FUNC printFunc) {

    PAdptArray adptArray = (PAdptArray) malloc(sizeof(AdptArray));
    if (adptArray != NULL) {
        adptArray->arrSize = 0;
        adptArray->elemArr = NULL;
        adptArray->copyFunction = copyFunc;
        adptArray->delFunction = delFunc;
        adptArray->printFunction = printFunc;
        return adptArray;
    }
    return NULL;
}

Result SetAdptArrayAt(PAdptArray adptArray, int index, PElement pNewElem) {

    if (adptArray == NULL) {
        return FAIL;
    }

    PElement *newpElemArr;

    /* if index is more than size of the old array, reallocate the old array to the correct size,
     * initialize rest elements with null, update Adpt array and size.
    */
    if (index >= adptArray->arrSize) {
        newpElemArr = (PElement *) realloc(adptArray->elemArr, (index + 1) * sizeof(PElement));
        if (newpElemArr == NULL) {
            return FAIL;
        }

        for (int i = adptArray->arrSize; i < index + 1; ++i) {
            newpElemArr[i] = NULL;
        }

        // Update array pointer and size
        adptArray->elemArr = newpElemArr;
        adptArray->arrSize = index + 1;
    }

    // Delete old element if exist
    if (adptArray->elemArr[index] != NULL) {
        adptArray->delFunction(adptArray->elemArr[index]);
    }

    // Initialize the array at the correct index in a copy of the new element
    if (pNewElem != NULL) {
        (adptArray->elemArr)[index] = adptArray->copyFunction(pNewElem);
    }
    return SUCCESS;
}

void DeleteAdptArray(PAdptArray adptArray) {

    if (adptArray == NULL) return;

    // Delete and free the pElement's array calling the delFunction
    for (int i = 0; i < adptArray->arrSize; ++i) {
        if ((adptArray->elemArr)[i] == NULL) continue;
        adptArray->delFunction((adptArray->elemArr)[i]);
    }

    // Free the pElements array then the Adpt array
    free(adptArray->elemArr);
    free(adptArray);
}

PElement GetAdptArrayAt(PAdptArray adptArray, int index) {

    if (index > adptArray->arrSize) return NULL;
    if ((adptArray->elemArr[index]) == NULL) return NULL;

    PElement elemCopy = adptArray->copyFunction(adptArray->elemArr[index]);

    return elemCopy;
}

int GetAdptArraySize(PAdptArray adptArray) {
    if (adptArray == NULL) return -1;
    return adptArray->arrSize;
}

void PrintDB(PAdptArray adptArray) {
    if (adptArray == NULL) return;
    for (int i = 0; i < adptArray->arrSize; ++i) {
        if (adptArray->elemArr[i] == NULL) continue;
        adptArray->printFunction(adptArray->elemArr[i]);
    }
}

