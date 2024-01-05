// 预处理指令，用于禁用某些函数的安全性警告
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

// 定义产品信息的结构体
struct Product {
    char name[6];         // 产品编号
    float unitPrice;      // 产品单价
    int soldQuantity;     // 销售数量
    int stockQuantity;    // 库存数量
    float weight;         // 产品重量
    float volume;         // 产品体积
    int returnQuantity;   // 退货数量
    float salesmoney;     // 销售金额
    float stockmoney;     // 库存金额
    float returnmoney;    // 退货金额
    int sortedIndex;      // 用来记录排序后的位置
};

// 定义全局变量，表示最大产品数量
#define MAX_PRODUCTS 10001

//读文件(将外存的txt读到内存)
//传入的变量是产品结构体的数组，和计数器记录产品数量
void readProducts(const char* fileName,struct Product products[], int* numProducts) {

    //此行声明了一个指向FILE结构体的指针，命名为file，并以只读模式（"r"）打开名为"fileName"的文件。
    //fopen函数返回指向已打开文件的指针。
    FILE* file = fopen(fileName, "r");

    //判断是否正确读入文件
    if (file == NULL) {
        printf("打开文件时发生错误。\n");
        exit(1);
    }

    //初始化计数器为0
    *numProducts = 0;

    //使用clock函数记录开始时间。这用于测量从文件中读取和处理数据所需的时间。
    clock_t start_time = clock();

    // 使用fscanf从文件中读取数据。它从文件的每一行中读取七个值。
    // 只要成功从文件中读取七个值，循环就会继续执行。
    while (fscanf(file, "%5s %f %d %d %f %f %d",
        products[*numProducts].name,
        &products[*numProducts].unitPrice,
        &products[*numProducts].soldQuantity,
        &products[*numProducts].stockQuantity,
        &products[*numProducts].weight,
        &products[*numProducts].volume,
        &products[*numProducts].returnQuantity) == 7) {

        // 数据是随机生成的，name会有重复，不读取
        // 检查是否已经存在相同的name
        int duplicate = 0;
        for (int i = 0; i < *numProducts; i++) {
            if (strcmp(products[i].name, products[*numProducts].name) == 0) {
                duplicate = 1;
                break;
            }
        }
        if (duplicate) {
            // 如果存在相同的name，不增加numProducts并继续下一轮循环
            continue;
        }

        // 要计算的三个值的就初始化为0.0
        products[*numProducts].salesmoney = 0.0;
        products[*numProducts].stockmoney = 0.0;
        products[*numProducts].returnmoney = 0.0;

        // 每次运行都将计数器++
        (*numProducts)++;

        // 判断边界条件
        if (*numProducts >= MAX_PRODUCTS) {
            printf("产品过多，请增加 MAX_PRODUCTS 的值。\n");
            exit(1);
        }
    }

    //到这里再次读取一下当前时间
    clock_t end_time = clock();

    //这里的时间与前面的时间相减，就可以得出读取文件的时间
    double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("1、读取数据花了%lf 秒。\n\n\n\n", elapsed_time);

    fclose(file);
}

//打印完整数据
void printProducts(struct Product products[], int numProducts) {
    printf("数据表格：\n");
    printf("产品名称\t单价\t销售数量\t库存数量\t重量\t体积\t退货数量\t销售额\t库存金额\t退款金额\n");
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

// 计算销售额、库存金额、退货金额，并记录计算所用的时间
void calculate(struct Product products[], int numProducts){
    // 使用clock函数记录开始时间
    clock_t start_time = clock();

    printf("编号\t\t销售额\t\t\t库存金额\t退款金额\n");
    for (int i = 0; i < numProducts; i++){
        // 计算销售额
        products[i].salesmoney = products[i].unitPrice * products[i].soldQuantity;
        // 计算库存金额
        products[i].stockmoney = products[i].unitPrice * products[i].stockQuantity;
        // 计算退货金额
        products[i].returnmoney = products[i].unitPrice * products[i].returnQuantity;
        printf("%s\t\t%f\t\t%f\t%f\n", products[i].name, products[i].salesmoney, products[i].stockmoney, products[i].returnmoney);
    }

    // 到这里再次读取一下当前时间
    clock_t end_time = clock();

    // 这里的时间与前面的时间相减，就可以得出计算的时间
    double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("\n2、计算销售额、库存金额、退货金额花了 %lf 秒。\n\n\n\n", elapsed_time);
}

//刷新文件(写文件操作)
void refreshFile(struct Product products[], int numProducts) {
    // 此行声明了一个指向FILE结构体的指针，命名为file，并以写入模式（"w"）打开名为"刷新后的文件.txt"的文件。
    FILE* file = fopen("刷新后的文件.txt", "w");

    //使用clock函数记录开始时间。这用于测量从文件中读取和处理数据所需的时间。
    clock_t start_time = clock();

    // 判断是否正确打开文件
    if (file == NULL) {
        printf("打开文件时发生错误。\n");
        exit(1);
    }

    // 将每个产品的信息写入文件
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

    printf("刷新文件成功，新文件名为\"刷新后的文件.txt\"。\n");
    //这里的时间与前面的时间相减，就可以得出读取文件的时间
    clock_t end_time = clock();
    double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("3、刷新数据花了%lf 秒。\n\n\n\n", elapsed_time);
    fclose(file);
}

// 直接插入排序以商品单价为关键字对数据进行排序
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
    printf("\n4、直接插入排序以商品单价为关键字花了 %lf 秒。\n", elapsed_time);
}

// 折半插入排序以销售数量为关键字对数据进行排序
void binaryInsertionSortBySoldQuantity(struct Product products[], int numProducts) {
    clock_t start_time = clock();
    for (int i = 1; i < numProducts; i++) {
        struct Product key = products[i];
        int low = 0, high = i - 1;

        // 二分查找插入位置
        while (low <= high) {
            int mid = (low + high) / 2;
            if (products[mid].soldQuantity < key.soldQuantity) {
                low = mid + 1;
            }
            else {
                high = mid - 1;
            }
        }

        // 移动元素以插入新元素
        for (int j = i - 1; j >= low; j--) {
            products[j + 1] = products[j];
        }
        // 插入新元素
        products[low] = key;
    }
    clock_t end_time = clock();
    double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("\n5、折半插入排序以销售数量为关键字花了 %lf 秒。\n", elapsed_time);
}

// 希尔排序以销售额为关键字对数据进行排序
void shellSortBySalesMoney(struct Product products[], int numProducts) {
    clock_t start_time = clock();
    int gap, i, j;
    struct Product temp;

    // 初始步长设置为数组长度的一半
    // 也就是先把数组分成gap/2个组，在组内进行排序，排序完，再变gap/4个组，继续排序，以此类推，直到gap==0
    for (gap = numProducts / 2; gap > 0; gap /= 2) {
        // 对每个步长进行插入排序
        for (i = gap; i < numProducts; i++) {
            temp = products[i];

            // 在当前步长内进行插入排序
            // 假设组内第一个元素已经排好，j一开始的位置就是一个组内的最后一个位置，然后将待插入元素进行对比插入合适的位置
            // 因为步长为gap，所以j要减少的是gap个位置，把j的位置就接收比temp大的值，也就是把大的放后面，实现升序
            for (j = i; j >= gap && products[j - gap].salesmoney > temp.salesmoney; j -= gap) {
                products[j] = products[j - gap];
            }

            // 插入当前元素到正确的位置
            products[j] = temp;
        }
    }
    clock_t end_time = clock();
    double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("\n6、希尔排序以销售额为关键字花了 %lf 秒。\n", elapsed_time);
}

// 冒泡排序以库存量为关键字对数据进行排序
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
    printf("\n7、冒泡排序以库存量为关键字花了 %lf 秒。\n", elapsed_time);
}

// 辅助函数，用于分区操作
int partitionByStockMoney(struct Product products[], int low, int high) {
    // 选择第一个元素为基准
    float pivot = products[low].stockmoney;
    int left = low + 1;
    int right = high;

    while (left <= right) {
        // 从右向左找第一个小于基准值的元素
        while (left <= right && products[right].stockmoney >= pivot) {
            right--;
        }

        // 从左向右找第一个大于基准值的元素
        while (left <= right && products[left].stockmoney < pivot) {
            left++;
        }

        // 交换找到的两个元素
        if (left <= right) {
            struct Product temp = products[left];
            products[left] = products[right];
            products[right] = temp;
            left++;
            right--;
        }
    }

    // 交换基准元素和最后一个小于基准的元素
    struct Product temp = products[low];
    products[low] = products[right];
    products[right] = temp;

    return right;
}

// 快速排序以库存金额为关键字对数据进行排序
void quickSortByStockMoney(struct Product products[], int low, int high) {
    if (low < high) {
        // 分区操作
        int pivotIndex = partitionByStockMoney(products, low, high);

        // 递归排序左右子数组
        quickSortByStockMoney(products, low, pivotIndex - 1);
        quickSortByStockMoney(products, pivotIndex + 1, high);
    }
}

// 选择排序以重量为关键字对数据进行排序
void selectionSortByWeight(struct Product products[], int numProducts) {
    clock_t start_time = clock();

    for (int i = 0; i < numProducts - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < numProducts; j++) {
            if (products[j].weight < products[minIndex].weight) {
                minIndex = j;
            }
        }

        // 交换products[i]和products[minIndex]
        struct Product temp = products[i];
        products[i] = products[minIndex];
        products[minIndex] = temp;
    }

    clock_t end_time = clock();
    double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("\n9、选择排序以重量为关键字花了 %lf 秒。\n", elapsed_time);
}

// 调整堆
void heapify(struct Product products[], int numProducts, int i) {
    int largest = i; // 初始化最大元素为根节点
    int left = 2 * i + 1; // 左子节点
    int right = 2 * i + 2; // 右子节点

    // 如果左子节点比根节点大
    if (left < numProducts && products[left].volume > products[largest].volume)
        largest = left;

    // 如果右子节点比根节点大
    if (right < numProducts && products[right].volume > products[largest].volume)
        largest = right;

    // 如果最大元素不是根节点
    if (largest != i) {
        // 交换根节点与最大元素
        struct Product temp = products[i];
        products[i] = products[largest];
        products[largest] = temp;

        // 递归调整被破坏的子堆
        heapify(products, numProducts, largest);
    }
}

// 堆排序以体积为关键字对数据进行排序
void heapSortByVolume(struct Product products[], int numProducts) {
    clock_t start_time = clock();

    // 构建最大堆
    for (int i = numProducts / 2 - 1; i >= 0; i--)
        heapify(products, numProducts, i);

    // 一个个从堆顶取出元素
    for (int i = numProducts - 1; i > 0; i--) {
        // 交换根节点与当前堆的最后一个节点
        struct Product temp = products[0];
        products[0] = products[i];
        products[i] = temp;

        // 调整新的根节点
        heapify(products, i, 0);
    }

    clock_t end_time = clock();
    double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("\n10、堆排序以体积为关键字花了 %lf 秒。\n", elapsed_time);
}

// 合并两个有序子数组
void merge(struct Product products[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // 创建动态分配的临时数组
    struct Product* L = (struct Product*)malloc(n1 * sizeof(struct Product));
    struct Product* R = (struct Product*)malloc(n2 * sizeof(struct Product));

    // 将数据复制到临时数组 L[] 和 R[]
    for (i = 0; i < n1; i++)
        L[i] = products[left + i];
    for (j = 0; j < n2; j++)
        R[j] = products[mid + 1 + j];

    // 归并临时数组到 products[left..right]
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

    // 复制 L[] 的剩余元素
    while (i < n1) {
        products[k] = L[i];
        i++;
        k++;
    }

    // 复制 R[] 的剩余元素
    while (j < n2) {
        products[k] = R[j];
        j++;
        k++;
    }

    // 释放动态分配的内存
    free(L);
    free(R);
}

// 归并排序以退货量为关键字对数据进行排序
void mergeSortByReturnQuantity(struct Product products[], int left, int right) {
    if (left < right) {
        // 计算中间点
        int mid = left + (right - left) / 2;

        // 递归排序左右子数组
        mergeSortByReturnQuantity(products, left, mid);
        mergeSortByReturnQuantity(products, mid + 1, right);

        // 合并两个子数组
        merge(products, left, mid, right);
    }
}

// 获取数组中的最大值
int getMax(int arr[], int num) {
    int max = arr[0];
    for (int i = 1; i < num; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

// 使用计数排序对数组按照指定的位进行排序
void countSort(int arr[], int num, int exp) {
    const int base = 10; // 基数为10
    int* output = (int*)malloc(num * sizeof(int));
    int* count = (int*)malloc(base * sizeof(int));

    // 初始化计数数组
    for (int i = 0; i < base; i++) {
        count[i] = 0;
    }

    // 计算每个数字的出现次数
    for (int i = 0; i < num; i++) {
        count[(arr[i] / exp) % base]++;
    }

    // 将 count[i] 累加到 count[i-1] 中，此时 count[i-1] 表示小于等于 i 的数字的个数
    for (int i = 1; i < base; i++) {
        count[i] += count[i - 1];
    }

    // 从后往前遍历原始数组，根据 count 数组中的信息放置元素到输出数组中
    for (int i = num - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % base] - 1] = arr[i];
        count[(arr[i] / exp) % base]--;
    }

    // 将输出数组复制到原始数组
    for (int i = 0; i < num; i++) {
        arr[i] = output[i];
    }

    // 释放动态分配的内存
    free(output);
    free(count);
}

// 基数排序对退货金额进行排序
void radixSortByReturnMoney(struct Product products[], int numProducts) {
    clock_t start_time = clock();

    int* returnMoneyInt = (int*)malloc(numProducts * sizeof(int));
    for (int i = 0; i < numProducts; i++) {
        returnMoneyInt[i] = (int)(products[i].returnmoney * 100);
    }

    int max = getMax(returnMoneyInt, numProducts);

    // 通过每一位进行计数排序
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countSort(returnMoneyInt, numProducts, exp);
    }

    // 将排序后的数据写回到原始数组
    for (int i = 0; i < numProducts; i++) {
        products[i].returnmoney = returnMoneyInt[i] / 100.0;
    }

    free(returnMoneyInt);

    clock_t end_time = clock();
    double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("\n12、基数排序对退货金额进行排序花了 %lf 秒。\n", elapsed_time);
}


// 输出前10个记录
void printTop10(struct Product products[], int numProducts) {
    printf("\n前10个记录（升序）：\n");
    printf("产品名称\t单价\t销售数量\t库存数量\t重量\t体积\t退货数量\t销售额\t库存金额\t退款金额\n");

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

// 菜单栏
void Menu(){
    printf("----------------------------------------------\n");
    printf("          企业的商品销售统计系统\n");
    printf("----------------------------------------------\n");
    printf("\t0. 退出系统\n");
    printf("\t1. 打印初始文件\n");
    printf("\t2. 计算销售额、库存金额、退货金额，并记录计算所用的时间\n");
    printf("\t3. 输出新数据\n");
    printf("\t4. 直接插入排序对商品单价进行排序\n");
    printf("\t5. 折半插入排序对销出数量进行排序\n");
    printf("\t6. 希尔排序对销售额进行排序\n");
    printf("\t7. 冒泡排序对库存量进行排序\n");
    printf("\t8. 快速排序对库存金额进行排序\n");
    printf("\t9. 选择排序对重量进行排序\n");
    printf("\t10. 堆排序对体积进行排序\n");
    printf("\t11. 归并排序对退货量进行排序\n");
    printf("\t12. 基数排序对退货金额进行排序\n");
    printf("\t13. 刷新文件(写文件操作)\n");
    printf("----------------------------------------------\n");
    printf("请输入您需要的功能：");
}

// 接受用户的需求
void Key(struct Product products[], int numProducts){
    // 读取用户输入
    int userKey = 0;
    scanf("%d", &userKey);
    // 初始化读取时间的功能变量
    clock_t start_time = clock();
    clock_t end_time = clock();
    double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    switch (userKey)
    {
    case 0:
        printf("【成功退出】\n");
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
        printf("\n8、快速排序以库存金额为关键字花了 %lf 秒。\n", elapsed_time);
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
        printf("\n11、归并排序以退货量为关键字花了 %lf 秒。\n", elapsed_time);
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

// 主函数
int main() {
    struct Product products[MAX_PRODUCTS];
    int numProducts;
    // 读文件
    readProducts("商品销售情况.txt", products, &numProducts);
    // 主菜单栏
    while (1)
    {
        Menu();
        Key(products,numProducts);
        system("pause");
        system("cls");
    }
    return 0;
}
