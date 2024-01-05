// Ԥ����ָ����ڽ���ĳЩ�����İ�ȫ�Ծ���
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

// �����Ʒ��Ϣ�Ľṹ��
struct Product {
    char name[6];         // ��Ʒ���
    float unitPrice;      // ��Ʒ����
    int soldQuantity;     // ��������
    int stockQuantity;    // �������
    float weight;         // ��Ʒ����
    float volume;         // ��Ʒ���
    int returnQuantity;   // �˻�����
    float salesmoney;     // ���۽��
    float stockmoney;     // �����
    float returnmoney;    // �˻����
    int sortedIndex;      // ������¼������λ��
};

// ����ȫ�ֱ�������ʾ����Ʒ����
#define MAX_PRODUCTS 10001

//���ļ�(������txt�����ڴ�)
//����ı����ǲ�Ʒ�ṹ������飬�ͼ�������¼��Ʒ����
void readProducts(const char* fileName,struct Product products[], int* numProducts) {

    //����������һ��ָ��FILE�ṹ���ָ�룬����Ϊfile������ֻ��ģʽ��"r"������Ϊ"fileName"���ļ���
    //fopen��������ָ���Ѵ��ļ���ָ�롣
    FILE* file = fopen(fileName, "r");

    //�ж��Ƿ���ȷ�����ļ�
    if (file == NULL) {
        printf("���ļ�ʱ��������\n");
        exit(1);
    }

    //��ʼ��������Ϊ0
    *numProducts = 0;

    //ʹ��clock������¼��ʼʱ�䡣�����ڲ������ļ��ж�ȡ�ʹ������������ʱ�䡣
    clock_t start_time = clock();

    // ʹ��fscanf���ļ��ж�ȡ���ݡ������ļ���ÿһ���ж�ȡ�߸�ֵ��
    // ֻҪ�ɹ����ļ��ж�ȡ�߸�ֵ��ѭ���ͻ����ִ�С�
    while (fscanf(file, "%5s %f %d %d %f %f %d",
        products[*numProducts].name,
        &products[*numProducts].unitPrice,
        &products[*numProducts].soldQuantity,
        &products[*numProducts].stockQuantity,
        &products[*numProducts].weight,
        &products[*numProducts].volume,
        &products[*numProducts].returnQuantity) == 7) {

        // ������������ɵģ�name�����ظ�������ȡ
        // ����Ƿ��Ѿ�������ͬ��name
        int duplicate = 0;
        for (int i = 0; i < *numProducts; i++) {
            if (strcmp(products[i].name, products[*numProducts].name) == 0) {
                duplicate = 1;
                break;
            }
        }
        if (duplicate) {
            // ���������ͬ��name��������numProducts��������һ��ѭ��
            continue;
        }

        // Ҫ���������ֵ�ľͳ�ʼ��Ϊ0.0
        products[*numProducts].salesmoney = 0.0;
        products[*numProducts].stockmoney = 0.0;
        products[*numProducts].returnmoney = 0.0;

        // ÿ�����ж���������++
        (*numProducts)++;

        // �жϱ߽�����
        if (*numProducts >= MAX_PRODUCTS) {
            printf("��Ʒ���࣬������ MAX_PRODUCTS ��ֵ��\n");
            exit(1);
        }
    }

    //�������ٴζ�ȡһ�µ�ǰʱ��
    clock_t end_time = clock();

    //�����ʱ����ǰ���ʱ��������Ϳ��Եó���ȡ�ļ���ʱ��
    double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("1����ȡ���ݻ���%lf �롣\n\n\n\n", elapsed_time);

    fclose(file);
}

//��ӡ��������
void printProducts(struct Product products[], int numProducts) {
    printf("���ݱ��\n");
    printf("��Ʒ����\t����\t��������\t�������\t����\t���\t�˻�����\t���۶�\t�����\t�˿���\n");
    for (int i = 0; i < numProducts; i++) {
        printf("%s\t\t", products[i].name);
        printf("%.2f\t", products[i].unitPrice);
        printf("%d\t\t", products[i].soldQuantity);
        printf("%d\t\t", products[i].stockQuantity);
        printf("%.2f\t", products[i].weight);
        printf("%.2f\t", products[i].volume);
        printf("%d\t\t", products[i].returnQuantity);
        printf("%.2f\t", products[i].salesmoney);
        printf("%.2f\t\t", products[i].stockmoney);
        printf("%.2f\t", products[i].returnmoney);
        printf("\n");
    }
}

// �������۶�����˻�������¼�������õ�ʱ��
void calculate(struct Product products[], int numProducts){
    // ʹ��clock������¼��ʼʱ��
    clock_t start_time = clock();

    printf("���\t\t���۶�\t\t\t�����\t�˿���\n");
    for (int i = 0; i < numProducts; i++){
        // �������۶�
        products[i].salesmoney = products[i].unitPrice * products[i].soldQuantity;
        // ��������
        products[i].stockmoney = products[i].unitPrice * products[i].stockQuantity;
        // �����˻����
        products[i].returnmoney = products[i].unitPrice * products[i].returnQuantity;
        printf("%s\t\t%f\t\t%f\t%f\n", products[i].name, products[i].salesmoney, products[i].stockmoney, products[i].returnmoney);
    }

    // �������ٴζ�ȡһ�µ�ǰʱ��
    clock_t end_time = clock();

    // �����ʱ����ǰ���ʱ��������Ϳ��Եó������ʱ��
    double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("\n2���������۶�����˻����� %lf �롣\n\n\n\n", elapsed_time);
}

//ˢ���ļ�(д�ļ�����)
void refreshFile(struct Product products[], int numProducts) {
    // ����������һ��ָ��FILE�ṹ���ָ�룬����Ϊfile������д��ģʽ��"w"������Ϊ"ˢ�º���ļ�.txt"���ļ���
    FILE* file = fopen("ˢ�º���ļ�.txt", "w");

    //ʹ��clock������¼��ʼʱ�䡣�����ڲ������ļ��ж�ȡ�ʹ������������ʱ�䡣
    clock_t start_time = clock();

    // �ж��Ƿ���ȷ���ļ�
    if (file == NULL) {
        printf("���ļ�ʱ��������\n");
        exit(1);
    }

    // ��ÿ����Ʒ����Ϣд���ļ�
    for (int i = 0; i < numProducts; i++) {
        fprintf(file, "%s\t\t%.2f\t%d\t\t%d\t\t%.2f\t%.2f\t%d\t\t%.2f\t%.2f\t%.2f\n",
            products[i].name,
            products[i].unitPrice,
            products[i].soldQuantity,
            products[i].stockQuantity,
            products[i].weight,
            products[i].volume,
            products[i].returnQuantity,
            products[i].salesmoney,
            products[i].stockmoney,
            products[i].returnmoney);
    }

    printf("ˢ���ļ��ɹ������ļ���Ϊ\"ˢ�º���ļ�.txt\"��\n");
    //�����ʱ����ǰ���ʱ��������Ϳ��Եó���ȡ�ļ���ʱ��
    clock_t end_time = clock();
    double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("3��ˢ�����ݻ���%lf �롣\n\n\n\n", elapsed_time);
    fclose(file);
}

// ֱ�Ӳ�����������Ʒ����Ϊ�ؼ��ֶ����ݽ�������
void insertionSortByUnitPrice(struct Product products[], int numProducts) {
    clock_t start_time = clock();
    for (int i = 1; i < numProducts; i++) {
        struct Product key = products[i];
        int j = i - 1;

        while (j >= 0 && products[j].unitPrice > key.unitPrice) {
            products[j + 1] = products[j];
            j = j - 1;
        }

        products[j + 1] = key;
    }
    clock_t end_time = clock();
    double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("\n4��ֱ�Ӳ�����������Ʒ����Ϊ�ؼ��ֻ��� %lf �롣\n", elapsed_time);
}

// �۰������������������Ϊ�ؼ��ֶ����ݽ�������
void binaryInsertionSortBySoldQuantity(struct Product products[], int numProducts) {
    clock_t start_time = clock();
    for (int i = 1; i < numProducts; i++) {
        struct Product key = products[i];
        int low = 0, high = i - 1;

        // ���ֲ��Ҳ���λ��
        while (low <= high) {
            int mid = (low + high) / 2;
            if (products[mid].soldQuantity < key.soldQuantity) {
                low = mid + 1;
            }
            else {
                high = mid - 1;
            }
        }

        // �ƶ�Ԫ���Բ�����Ԫ��
        for (int j = i - 1; j >= low; j--) {
            products[j + 1] = products[j];
        }
        // ������Ԫ��
        products[low] = key;
    }
    clock_t end_time = clock();
    double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("\n5���۰������������������Ϊ�ؼ��ֻ��� %lf �롣\n", elapsed_time);
}

// ϣ�����������۶�Ϊ�ؼ��ֶ����ݽ�������
void shellSortBySalesMoney(struct Product products[], int numProducts) {
    clock_t start_time = clock();
    int gap, i, j;
    struct Product temp;

    // ��ʼ��������Ϊ���鳤�ȵ�һ��
    // Ҳ�����Ȱ�����ֳ�gap/2���飬�����ڽ������������꣬�ٱ�gap/4���飬���������Դ����ƣ�ֱ��gap==0
    for (gap = numProducts / 2; gap > 0; gap /= 2) {
        // ��ÿ���������в�������
        for (i = gap; i < numProducts; i++) {
            temp = products[i];

            // �ڵ�ǰ�����ڽ��в�������
            // �������ڵ�һ��Ԫ���Ѿ��źã�jһ��ʼ��λ�þ���һ�����ڵ����һ��λ�ã�Ȼ�󽫴�����Ԫ�ؽ��жԱȲ�����ʵ�λ��
            // ��Ϊ����Ϊgap������jҪ���ٵ���gap��λ�ã���j��λ�þͽ��ձ�temp���ֵ��Ҳ���ǰѴ�ķź��棬ʵ������
            for (j = i; j >= gap && products[j - gap].salesmoney > temp.salesmoney; j -= gap) {
                products[j] = products[j - gap];
            }

            // ���뵱ǰԪ�ص���ȷ��λ��
            products[j] = temp;
        }
    }
    clock_t end_time = clock();
    double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("\n6��ϣ�����������۶�Ϊ�ؼ��ֻ��� %lf �롣\n", elapsed_time);
}

// ð�������Կ����Ϊ�ؼ��ֶ����ݽ�������
void bubbleSortByStockQuantity(struct Product products[], int numProducts) {
    clock_t start_time = clock();
    for (int i = 0; i < numProducts - 1; i++) {
        for (int j = 0; j < numProducts - i - 1; j++) {
            if (products[j].stockQuantity > products[j + 1].stockQuantity) {
                struct Product temp = products[j];
                products[j] = products[j + 1];
                products[j + 1] = temp;
            }
        }
    }
    clock_t end_time = clock();
    double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("\n7��ð�������Կ����Ϊ�ؼ��ֻ��� %lf �롣\n", elapsed_time);
}

// �������������ڷ�������
int partitionByStockMoney(struct Product products[], int low, int high) {
    // ѡ���һ��Ԫ��Ϊ��׼
    float pivot = products[low].stockmoney;
    int left = low + 1;
    int right = high;

    while (left <= right) {
        // ���������ҵ�һ��С�ڻ�׼ֵ��Ԫ��
        while (left <= right && products[right].stockmoney >= pivot) {
            right--;
        }

        // ���������ҵ�һ�����ڻ�׼ֵ��Ԫ��
        while (left <= right && products[left].stockmoney < pivot) {
            left++;
        }

        // �����ҵ�������Ԫ��
        if (left <= right) {
            struct Product temp = products[left];
            products[left] = products[right];
            products[right] = temp;
            left++;
            right--;
        }
    }

    // ������׼Ԫ�غ����һ��С�ڻ�׼��Ԫ��
    struct Product temp = products[low];
    products[low] = products[right];
    products[right] = temp;

    return right;
}

// ���������Կ����Ϊ�ؼ��ֶ����ݽ�������
void quickSortByStockMoney(struct Product products[], int low, int high) {
    if (low < high) {
        // ��������
        int pivotIndex = partitionByStockMoney(products, low, high);

        // �ݹ���������������
        quickSortByStockMoney(products, low, pivotIndex - 1);
        quickSortByStockMoney(products, pivotIndex + 1, high);
    }
}

// ѡ������������Ϊ�ؼ��ֶ����ݽ�������
void selectionSortByWeight(struct Product products[], int numProducts) {
    clock_t start_time = clock();

    for (int i = 0; i < numProducts - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < numProducts; j++) {
            if (products[j].weight < products[minIndex].weight) {
                minIndex = j;
            }
        }

        // ����products[i]��products[minIndex]
        struct Product temp = products[i];
        products[i] = products[minIndex];
        products[minIndex] = temp;
    }

    clock_t end_time = clock();
    double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("\n9��ѡ������������Ϊ�ؼ��ֻ��� %lf �롣\n", elapsed_time);
}

// ������
void heapify(struct Product products[], int numProducts, int i) {
    int largest = i; // ��ʼ�����Ԫ��Ϊ���ڵ�
    int left = 2 * i + 1; // ���ӽڵ�
    int right = 2 * i + 2; // ���ӽڵ�

    // ������ӽڵ�ȸ��ڵ��
    if (left < numProducts && products[left].volume > products[largest].volume)
        largest = left;

    // ������ӽڵ�ȸ��ڵ��
    if (right < numProducts && products[right].volume > products[largest].volume)
        largest = right;

    // ������Ԫ�ز��Ǹ��ڵ�
    if (largest != i) {
        // �������ڵ������Ԫ��
        struct Product temp = products[i];
        products[i] = products[largest];
        products[largest] = temp;

        // �ݹ�������ƻ����Ӷ�
        heapify(products, numProducts, largest);
    }
}

// �����������Ϊ�ؼ��ֶ����ݽ�������
void heapSortByVolume(struct Product products[], int numProducts) {
    clock_t start_time = clock();

    // ��������
    for (int i = numProducts / 2 - 1; i >= 0; i--)
        heapify(products, numProducts, i);

    // һ�����ӶѶ�ȡ��Ԫ��
    for (int i = numProducts - 1; i > 0; i--) {
        // �������ڵ��뵱ǰ�ѵ����һ���ڵ�
        struct Product temp = products[0];
        products[0] = products[i];
        products[i] = temp;

        // �����µĸ��ڵ�
        heapify(products, i, 0);
    }

    clock_t end_time = clock();
    double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("\n10�������������Ϊ�ؼ��ֻ��� %lf �롣\n", elapsed_time);
}

// �ϲ���������������
void merge(struct Product products[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // ������̬�������ʱ����
    struct Product* L = (struct Product*)malloc(n1 * sizeof(struct Product));
    struct Product* R = (struct Product*)malloc(n2 * sizeof(struct Product));

    // �����ݸ��Ƶ���ʱ���� L[] �� R[]
    for (i = 0; i < n1; i++)
        L[i] = products[left + i];
    for (j = 0; j < n2; j++)
        R[j] = products[mid + 1 + j];

    // �鲢��ʱ���鵽 products[left..right]
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (L[i].returnQuantity <= R[j].returnQuantity) {
            products[k] = L[i];
            i++;
        }
        else {
            products[k] = R[j];
            j++;
        }
        k++;
    }

    // ���� L[] ��ʣ��Ԫ��
    while (i < n1) {
        products[k] = L[i];
        i++;
        k++;
    }

    // ���� R[] ��ʣ��Ԫ��
    while (j < n2) {
        products[k] = R[j];
        j++;
        k++;
    }

    // �ͷŶ�̬������ڴ�
    free(L);
    free(R);
}

// �鲢�������˻���Ϊ�ؼ��ֶ����ݽ�������
void mergeSortByReturnQuantity(struct Product products[], int left, int right) {
    if (left < right) {
        // �����м��
        int mid = left + (right - left) / 2;

        // �ݹ���������������
        mergeSortByReturnQuantity(products, left, mid);
        mergeSortByReturnQuantity(products, mid + 1, right);

        // �ϲ�����������
        merge(products, left, mid, right);
    }
}

// ��ȡ�����е����ֵ
int getMax(int arr[], int num) {
    int max = arr[0];
    for (int i = 1; i < num; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

// ʹ�ü�����������鰴��ָ����λ��������
void countSort(int arr[], int num, int exp) {
    const int base = 10; // ����Ϊ10
    int* output = (int*)malloc(num * sizeof(int));
    int* count = (int*)malloc(base * sizeof(int));

    // ��ʼ����������
    for (int i = 0; i < base; i++) {
        count[i] = 0;
    }

    // ����ÿ�����ֵĳ��ִ���
    for (int i = 0; i < num; i++) {
        count[(arr[i] / exp) % base]++;
    }

    // �� count[i] �ۼӵ� count[i-1] �У���ʱ count[i-1] ��ʾС�ڵ��� i �����ֵĸ���
    for (int i = 1; i < base; i++) {
        count[i] += count[i - 1];
    }

    // �Ӻ���ǰ����ԭʼ���飬���� count �����е���Ϣ����Ԫ�ص����������
    for (int i = num - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % base] - 1] = arr[i];
        count[(arr[i] / exp) % base]--;
    }

    // ��������鸴�Ƶ�ԭʼ����
    for (int i = 0; i < num; i++) {
        arr[i] = output[i];
    }

    // �ͷŶ�̬������ڴ�
    free(output);
    free(count);
}

// ����������˻�����������
void radixSortByReturnMoney(struct Product products[], int numProducts) {
    clock_t start_time = clock();

    int* returnMoneyInt = (int*)malloc(numProducts * sizeof(int));
    for (int i = 0; i < numProducts; i++) {
        returnMoneyInt[i] = (int)(products[i].returnmoney * 100);
    }

    int max = getMax(returnMoneyInt, numProducts);

    // ͨ��ÿһλ���м�������
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countSort(returnMoneyInt, numProducts, exp);
    }

    // ������������д�ص�ԭʼ����
    for (int i = 0; i < numProducts; i++) {
        products[i].returnmoney = returnMoneyInt[i] / 100.0;
    }

    free(returnMoneyInt);

    clock_t end_time = clock();
    double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("\n12������������˻������������� %lf �롣\n", elapsed_time);
}


// ���ǰ10����¼
void printTop10(struct Product products[], int numProducts) {
    printf("\nǰ10����¼�����򣩣�\n");
    printf("��Ʒ����\t����\t��������\t�������\t����\t���\t�˻�����\t���۶�\t�����\t�˿���\n");

    int topCount = (numProducts < 10) ? numProducts : 10;

    for (int i = 0; i < topCount; i++) {
        printf("%s\t\t", products[i].name);
        printf("%.2f\t", products[i].unitPrice);
        printf("%d\t\t", products[i].soldQuantity);
        printf("%d\t\t", products[i].stockQuantity);
        printf("%.2f\t", products[i].weight);
        printf("%.2f\t", products[i].volume);
        printf("%d\t\t", products[i].returnQuantity);
        printf("%.2f\t", products[i].salesmoney);
        printf("%.2f\t\t", products[i].stockmoney);
        printf("%.2f\t", products[i].returnmoney);
        printf("\n");
    }
}

// �˵���
void Menu(){
    printf("----------------------------------------------\n");
    printf("          ��ҵ����Ʒ����ͳ��ϵͳ\n");
    printf("----------------------------------------------\n");
    printf("\t0. �˳�ϵͳ\n");
    printf("\t1. ��ӡ��ʼ�ļ�\n");
    printf("\t2. �������۶�����˻�������¼�������õ�ʱ��\n");
    printf("\t3. ���������\n");
    printf("\t4. ֱ�Ӳ����������Ʒ���۽�������\n");
    printf("\t5. �۰�������������������������\n");
    printf("\t6. ϣ����������۶��������\n");
    printf("\t7. ð������Կ������������\n");
    printf("\t8. ��������Կ�����������\n");
    printf("\t9. ѡ�������������������\n");
    printf("\t10. ������������������\n");
    printf("\t11. �鲢������˻�����������\n");
    printf("\t12. ����������˻�����������\n");
    printf("\t13. ˢ���ļ�(д�ļ�����)\n");
    printf("----------------------------------------------\n");
    printf("����������Ҫ�Ĺ��ܣ�");
}

// �����û�������
void Key(struct Product products[], int numProducts){
    // ��ȡ�û�����
    int userKey = 0;
    scanf("%d", &userKey);
    // ��ʼ����ȡʱ��Ĺ��ܱ���
    clock_t start_time = clock();
    clock_t end_time = clock();
    double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    switch (userKey)
    {
    case 0:
        printf("���ɹ��˳���\n");
        exit(0);
        break;

    case 1:
        printProducts(products,numProducts);
        break;

    case 2:
        calculate(products, numProducts);
        break;

    case 3:
        printProducts(products,numProducts);
        break;

    case 4:
        insertionSortByUnitPrice(products, numProducts);
        printTop10(products, numProducts);
        break;
     
    case 5:
        binaryInsertionSortBySoldQuantity(products, numProducts);
        printTop10(products, numProducts);
        break;

    case 6:
        shellSortBySalesMoney(products, numProducts);
        printTop10(products, numProducts);
        break;

    case 7:
        bubbleSortByStockQuantity(products, numProducts);
        printTop10(products, numProducts);
        break;
        
    case 8:        
        start_time = clock();
        quickSortByStockMoney(products, 0, numProducts - 1);
        end_time = clock();
        elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        printf("\n8�����������Կ����Ϊ�ؼ��ֻ��� %lf �롣\n", elapsed_time);
        printTop10(products, numProducts);
        break;

    case 9:
        selectionSortByWeight(products, numProducts);
        printTop10(products, numProducts);
        break;

    case 10:
        heapSortByVolume(products, numProducts);
        printTop10(products, numProducts);
        break;

    case 11:
        start_time = clock();
        mergeSortByReturnQuantity(products, 0, numProducts - 1);
        end_time = clock();
        elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        printf("\n11���鲢�������˻���Ϊ�ؼ��ֻ��� %lf �롣\n", elapsed_time);
        printTop10(products, numProducts);
        break;

    case 12:
        radixSortByReturnMoney(products, numProducts);
        printTop10(products, numProducts);
        break;

    case 13:
        refreshFile(products, numProducts);
        break;
    }
}

// ������
int main() {
    struct Product products[MAX_PRODUCTS];
    int numProducts;
    // ���ļ�
    readProducts("��Ʒ�������.txt", products, &numProducts);
    // ���˵���
    while (1)
    {
        Menu();
        Key(products,numProducts);
        system("pause");
        system("cls");
    }
    return 0;
}
