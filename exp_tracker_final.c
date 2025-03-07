
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define NAME_LEN 50
#define CATEGORY_LEN 50



typedef struct Node_tag {
    int data ;
    struct Node_tag* next;
} Node;

typedef struct user{
    unsigned int user_id;
    char name[NAME_LEN];
    float income;
    struct user* next ;
} user ;

typedef struct expense{
    unsigned int expense_id;
    char expense_cat[CATEGORY_LEN];// also check for whether date will be int or string 
    float exp_amt;
    int date;
    unsigned int member_id ; // same as the user id one 
    struct expense* next ;
    
} expense;

typedef struct fam{
    unsigned int fam_id; // this will be referenced from struct user 
    int count;// keeping track of number of family members
    user* next_user ;// given a pointer to a node of type user, so that family members can be represented using a linked list within a fam node
    char fam_name[NAME_LEN];
    float fam_income,fam_expense;
    struct fam* next ;
    
}fam;

typedef struct cat_exp{
    float exp_amt ;
    char exp_cat[CATEGORY_LEN];
    struct cat_exp* next ;
} cat_rec;

void printList(Node* lptr){
    Node* nptr;
    nptr = lptr ;
    while(nptr != NULL){
        printf("%d->", nptr->data);
        nptr = nptr->next;
    }
}

cat_rec* createList(){

    cat_rec* lptr,*nptr, *tail, *start ;
    int data;
    lptr = (cat_rec*)malloc(sizeof(cat_rec));//dummy cat_rec 
    tail = lptr ;
    for(int i =0 ; i<5 ; i++){
        nptr = (cat_rec*)malloc(sizeof(cat_rec));
        tail->next = nptr ;
        tail = nptr ;
    }
    start = lptr ;
    lptr = lptr->next ;
    free(start) ;
    start = NULL;

    return lptr ;
}


Node* mergeTwoLists(Node* list1, Node* list2) {

    Node* result, *ptr1, *ptr2, *tail;
    ptr1 = list1;
    ptr2 = list2;
    if((list1 != NULL) && (list2 != NULL)){
        if(list1->data < list2->data){
        result = tail = list1;
        ptr1 = ptr1->next;
        }
        else{
            result = tail = list2;
            ptr2 = ptr2->next;
        }
        while((ptr1 != NULL) && (ptr2 != NULL)){
            if(ptr1->data < ptr2->data){
                tail->next = ptr1;
                tail = tail->next;
                ptr1 = ptr1->next;
            }
            else{
                tail = tail->next = ptr2;
                ptr2 = ptr2->next;
            }
        }

        if(ptr1 != NULL){
            tail->next = ptr1;
        }
        else{
            tail->next = ptr2;
        }
    }
    else{
        if(list1 == NULL){
            result = list2;
        }
        else{
            result = list1;
        }
    }
        
    return result ;
}

user* insertionSortUser(user* lptr, user*nptr) {
    if ((lptr == NULL)) {
        return nptr; // already when i will be passing nptr which has been formed from makenode function its next will be set to null
    }
    else if (lptr->next == NULL){
        if(nptr->user_id < lptr->user_id){
            nptr->next = lptr ;
            return nptr ;
        }
        else{
            lptr->next = nptr ;
            return lptr ;
        }
    }
    else{
        int flag =0 ;
        user* dummy = malloc(sizeof(user));
        dummy->next = lptr;

        user* prev = lptr;
        user* cur = lptr->next;

        while ((cur) &&(!flag)) {
            // already in-order
            if (cur->user_id <= nptr->user_id) {
                prev = cur;
                cur = cur->next;
            } 
            else {
                user* temp = dummy;
                
                while(nptr->user_id > temp->next->user_id) 
                    temp = temp->next;

                // find the stop
                temp->next = nptr;
                nptr->next = cur;
                prev= prev->next ;
                flag = 1;
                
            }
        }
        if(cur == NULL){
            prev->next = nptr;
        }
        return dummy->next;
    }
    
}

expense* insertionSortExpense(expense* lptr, expense* nptr){
    if ((lptr == NULL)) {
        return nptr; // already when i will be passing nptr which has been formed from makenode function its next will be set to null
    }
    else if (lptr->next == NULL){
        if((nptr->member_id < lptr->member_id) || (nptr->member_id == lptr->member_id) &&(nptr->expense_id < lptr->expense_id)){
            nptr->next = lptr ;
            return nptr ;
        }
        
        else{
            lptr->next = nptr ;
            return lptr ;
        }
    }
    else{
        int flag =0 ;
        expense* dummy = malloc(sizeof(expense));
        dummy->next = lptr;

        expense* prev = lptr;
        expense* cur = lptr->next;

        while ((cur) &&(!flag)) {
            // already in-order
            if ((cur->member_id < nptr->member_id)||(cur->member_id == nptr->member_id)&&(cur->expense_id < nptr->expense_id) ){
                prev = cur;
                cur = cur->next;
            } 
            else {
                expense* temp = dummy;
                
                while((nptr->member_id > temp->next->member_id)||(nptr->member_id == temp->next->member_id)&&(nptr->expense_id > temp->next->expense_id)) 
                    temp = temp->next;

                // find the stop
                temp->next = nptr;
                nptr->next = cur;
                prev= prev->next ;
                flag = 1;
                
            }
        }
        if(cur == NULL){
            prev->next = nptr;
        }
        return dummy->next;
    }    


}

Node* divide(Node* lptr){
    Node* nptr, *fast , *slow ;
    fast = lptr->next->next ;
    slow = lptr ;

    while(fast != NULL){
        slow = slow->next ;
        fast = fast->next ;
        if(fast->next != NULL){
            fast = fast->next ;
        }
    }
    nptr = slow->next ;
    slow->next = NULL ;
    return nptr ;
}

Node* mergeSort(Node* lptr){
    Node* nptr, *list_ptr;
    list_ptr = lptr ;
    nptr = divide(list_ptr);
    list_ptr = mergeSort(list_ptr);
    nptr = mergeSort(nptr);
    lptr = mergeTwoLists(nptr , list_ptr) ; 
    return lptr ;

}




fam* makeNode_fam(unsigned int fam_id ,float fam_income,float fam_expense,char fam_name[NAME_LEN],int count, user* next_user ){

    fam* nptr ;
    nptr = (fam*)malloc(sizeof(fam));
    if(nptr != NULL){
        nptr->count = count;
        nptr->fam_id = fam_id;
        nptr->fam_expense = fam_expense;
        nptr->fam_income = fam_income ;
        nptr->next_user = next_user ;
        strcpy(nptr->fam_name, fam_name);
        nptr->next = NULL;
    }
    else{
        nptr = NULL ;
        printf("Memory dosent exist \n");
    }
    return nptr ;
}


expense* makeNode_expense(unsigned int exp_id ,float exp_amt,char exp_cat[],int date,unsigned int mem_id ){

    expense* nptr ;
    nptr = (expense*)malloc(sizeof(expense));
    if(nptr != NULL){
        nptr->exp_amt = exp_amt ;
        nptr->expense_id = exp_id ;
        strcpy(nptr->expense_cat , exp_cat);
        nptr->date = date;
        nptr->member_id = mem_id ;
        nptr->next = NULL;
    }
    else{
        nptr = NULL ;
        printf("Memory dosent exist \n");
    }
    return nptr ;
}

user* makeNode_user(unsigned int mem_id ,float income_user,char name_user[] ){

    user* nptr ;
    nptr = (user*)malloc(sizeof(user));
    if(nptr != NULL){
        nptr->income = income_user ;
        nptr->user_id = mem_id ;
        
        strcpy(nptr->name , name_user);
        nptr->next = NULL;
    }
    else{
        nptr = NULL ;
        printf("Memory dosent exist \n");
    }
    return nptr ;
}


void create_joinFamily(int* cj, fam** f1, user* made_from_makeuser,int* fam_id); //prototype
void addUser(user** users, int* cj, int* family_id, fam** f1){ 
    // we are passing the head of the user linked list as an argument ;
    user* nptr ;
    user* ptr, *ptr2;
    int flag = 1;
    int id;
    float money_in ;
    char std_name[NAME_LEN];
   
    while(flag == 1){
        flag = 0 ;
        printf("Enter userId \n");
        scanf("%d",&id);
        ptr = *users ;
        while((ptr != NULL)&&(flag==0)){
            if(ptr->user_id == id){
                flag =1;
                printf("Id already exists \n");
            }
            else{
                ptr = ptr->next ;
            }
        }
        if(ptr == NULL){
            printf("Enter name: \n");
            scanf("%s",std_name);

            printf("Enter income: \n");
            scanf("%f",&money_in);
        }

    }

    nptr = makeNode_user(id,money_in,std_name);
    user* kptr = makeNode_user(id,money_in,std_name);
    *users = insertionSortUser(*users,nptr) ;

    int flag_fam=1;
    
    while(flag_fam==1){
        printf("Enter 1 if you want to create a family or enter 0 if you want to join a family \n");
        scanf("%d",cj);
        // maybe possible that cj needs to be defined globally because it is required in the create_joinFamily function
        // it has been resolved by using a pointer 
        if(*cj==1){
            create_joinFamily(cj,f1,kptr,family_id); 
            flag_fam=0;
        }
        else if(*cj==0){
            create_joinFamily(cj,f1,kptr,family_id); 
            flag_fam=0;
        }
        else{
            printf("Invalid input");
            
        }
    }
    printf("User added \n");
}

void addExpense(expense** e1, user** u1, fam** f1){

    int id, is_true_user = 1 ;
    int found = 0, found1 =1, found2 = 0;
    int exp_id, date;
    float money_out;
    char exp_cat[CATEGORY_LEN];

    while(is_true_user == 1){
        printf("Enter the user id of the person whose expense record is to be stored: \n");
        scanf("%d",&id);
        // try passing the head of user as an argument to the add_expense function 
        user* ptr = *u1 ; // check
        while((ptr != NULL)&&(!found)){
            if(ptr->user_id == id){
                found = 1;
            }
            else{
                ptr = ptr->next ;
            }
        }
        if(found == 0){
            is_true_user = 1;
        }
        else{
            is_true_user = 0 ;
            expense* ptr1 = *e1 ;
            while(found1 == 1){
                found1 = 0 ;
                printf("Give expense id: \n");
                scanf("%d",&exp_id);
                while((ptr1 != NULL)&&(found1 == 0)){
                    if(ptr1->expense_id == exp_id){
                        found1 = 1;
                        printf("Expense id already exists \n");
                    }
                    else{
                        ptr1 = ptr1->next ;
                    }
                }
                if(ptr1 == NULL){
                    printf("Enter expense category: \n");
                    scanf("%s",exp_cat);
                    printf("Enter expense amount: \n");
                    scanf("%f",&money_out);
                    printf("Enter date of transaction:(between 1 and 10) \n");
                    scanf("%d",&date);
                }
            }

            expense* nptr = makeNode_expense(exp_id,money_out,exp_cat,date,id);
            *e1 = insertionSortExpense(*e1,nptr) ;

            //write a code to search both family and user ll On^2 and then upon getting the persons id we need to append it to the family's expense
            

            fam* ptr_tr_1 =  *f1;
            

            while((ptr_tr_1 != NULL)&&(found2 == 0)){
                user* ptr_tr_2 = ptr_tr_1->next_user;
                while((ptr_tr_2 != NULL)&&(found2 == 0)){
                    if(ptr_tr_2->user_id == id){
                        ptr_tr_1->fam_expense += nptr->exp_amt;
                        found2 = 1;
                    }
                    else{
                        ptr_tr_2 = ptr_tr_2->next ;
                    }
                    
                }
                ptr_tr_1 = ptr_tr_1->next;
            }

            printf("Expense added \n");
            
        }

    }
    

}

void create_joinFamily(int* cj, fam** f1, user* made_from_makeuser,int*fam_id){

    char std_fam_name[NAME_LEN];
    float fam_income = 0.00, fam_expense = 0.00 ;
    int count = 0 ;
    
    
    
    fam* fptr ;

    if(*cj == 1){

        printf("Enter name of family: ");
        scanf("%s",std_fam_name);
        fam_income += made_from_makeuser->income ;
        count += 1;
        *fam_id = *fam_id + 1;
        fptr = makeNode_fam(*fam_id,fam_income,fam_expense,std_fam_name,count,made_from_makeuser);
        // but remember ki tujhe madefrommakeuser me change lana hai , so double pointer pass karsakta hai 
        fam*ptr = *f1 ;
        while((ptr != NULL)&&(ptr->next != NULL)){
            ptr = ptr->next ;
        }

        if(ptr == NULL){
            *f1 = fptr ;
        }
        else{
            ptr->next = fptr ;
        }
        
        printf("Family id is : %d\n",*fam_id);  

    }
    else{
        int family_id, fam_id_found = 0;
        while(fam_id_found == 0){

            printf("Enter the family_id of the family you want to join: \n");
            scanf("%d",&family_id);

            //search if it exists 

            fam* ptr1 = *f1;
            fam* family;
            int flag =0 ;
            while((ptr1 != NULL)&&(flag ==0)){
                if(ptr1->fam_id == family_id){
                    flag = 1;
                    family = ptr1;
                }
                else{
                    ptr1 = ptr1->next ;
                }
            }

            
            // aply an if statemnt saying if count<4 do this else print max limit reached 
            if(flag ==1)
            {
                if(family->count <4){
                    //seedhafamily ke next_user ko access karke usme ye user daaldena hai
                    fam_id_found = 1;
                    user* ptr3 = family->next_user;
                    // here ptr3 cannot be null since it has been handled earlier itself when the family was being formed 
                    while((ptr3 != NULL)&&(ptr3->next != NULL)){

                        ptr3 = ptr3->next ;
                    }
                    ptr3->next = made_from_makeuser ;
                    family->fam_income = family->fam_income + made_from_makeuser->income;
                    family->count += 1;
                    }
                    else{
                        printf("Family limit exceeded\n");
                    } 
            }
            else{
                printf("Family id doesent exist\n");
            }

        }
        
        
    }
}

void removeFromListUser(user** u1, user* target) {

    if (u1 == NULL || *u1 == NULL || target == NULL) {
        return;  
    }

    user* temp = *u1;
    user* prev = NULL;

    if (temp == target) {  // If the target is the head node
        *u1 = target->next;
    } 
    else {
        while (temp != NULL && temp != target) {
            prev = temp;
            temp = temp->next;
        }
        if (temp == target) {  // If target is found
            prev->next = target->next;
        }
    }

    if (temp == target) {  // Free the node if it was found
        free(target);
    }
}

void removeFromListFam(fam** f1, fam* target) {
    if (f1 == NULL || *f1 == NULL || target == NULL) {
        return;  
    }

    fam* temp = *f1;
    fam* prev = NULL;

    if (temp == target) {  // If the target is the head node
        *f1 = target->next;
    } 
    else {
        while (temp != NULL && temp != target) {
            prev = temp;
            temp = temp->next;
        }
        if (temp == target) {  // If target is found
            prev->next = target->next;
        }
    }

    if (temp == target) {  // Free the node if it was found
        free(target);
    }
}

void removeFromListExpense(expense** e1, expense* target) {
    if (e1 == NULL || *e1 == NULL || target == NULL) {
        return;  
    }

    expense* temp = *e1;
    expense* prev = NULL;

    if (temp == target) {  // If the target is the head node
        *e1 = target->next;
    } 
    else {
        while (temp != NULL && temp != target) {
            prev = temp;
            temp = temp->next;
        }
        if (temp == target) {  // If target is found
            prev->next = target->next;
        }
    }

    if (temp == target) {  // Free the node if it was found
        free(target);
    }
}


void update_individual_fam_details(user**u1, fam**f1){
    int flag, flag2, flag3, id, found_user = 0, fam_id, found_fam = 0, user_id_del, del_user = 0, found_ind_del = 0, fam_id_del, del_fam = 0, upd_user_flag = 0;
    float upd_income;
    char upd_name[NAME_LEN], fam_upd_name[NAME_LEN];
    user* user_detail_chng, *user_detail_del;
    fam* fam_detail_chng, *fam_detail_del;

    printf("Do you want to delete or update records? delete=1, update=0: \n");
    scanf("%d",&flag);
    if(flag == 0){
        printf("Which information do you want to change, individual or family? (family 1/individual 0) \n");
        scanf("%d",&flag2);
        if(flag2 == 0){
            //update individual details
            printf("Which user id information do u want to change: \n");
            scanf("%d",&id);
            user* ptr = *u1;
            while((ptr != NULL)&&(found_user == 0)){
                if(ptr->user_id == id){
                    found_user = 1;
                    user_detail_chng = ptr ;
                }
                else{
                    ptr = ptr->next ;
                }
            }
            if(found_user == 1){
                printf("If name has to be changed give different name, else provide the same name: \n");
                scanf("%s",upd_name);
                strcpy(user_detail_chng->name , upd_name);
                printf("If u want to change the income, give new income else give old income: \n");
                scanf("%f",&upd_income);
                user_detail_chng->income = upd_income ;

                //now change it for the fmily ll

                fam* ptr4 =  *f1;
                

                while((ptr4 != NULL)&&(upd_user_flag == 0)){
                    user* ptr5 = ptr4->next_user;
                    while((ptr5 != NULL)&&(upd_user_flag == 0)){
                        if(ptr5->user_id == id){
                            strcpy(ptr5->name, upd_name);
                            ptr5->income = upd_income;
                            upd_user_flag = 1;
                        }
                        ptr5 = ptr5->next ;
                    }
                    ptr4 = ptr4->next;
                }

            }
            else{
                printf("User not Found \n"); // if need be we can add this in a while loop 
            }
        }
        else{
            //update family details
            printf("Which fam id information do u want to change: \n");
            scanf("%d",&fam_id);
            fam* ptr1 = *f1;
            while((ptr1 != NULL)&&(found_fam == 0)){
                if(ptr1->fam_id == fam_id){
                    found_fam = 1;
                    fam_detail_chng = ptr1 ;
                }
                else{
                    ptr1 = ptr1->next ;
                }
            }
            if(found_fam == 1){
                printf("If name has to be changed give different name, else provide the same name: \n");
                scanf("%s",fam_upd_name);
                strcpy(fam_detail_chng->fam_name,fam_upd_name);
            }
            else{
                printf("Family not found\n");
            }
        }

    }

    else{
        //for deletion 
        printf("Which information do you want to delete, individual or family? (family 1/individual 0) \n");
        scanf("%d",&flag3);
        if(flag3==0){
            //need to note that heap locatin is same for user node in userlist and user node in family list since we are using the same nptr in both cases
            // therefore freeing one pointer will lead to a dangling pointer for the other and vice versa 
            // we will remove them from their rerpective lists and then free them together 

            printf("Which user id information do u want to delete: \n");
            scanf("%d",&user_id_del);
            user*ptr2 = *u1;
            while((ptr2 != NULL)&&(del_user == 0)){
                if(ptr2->user_id == user_id_del){
                    del_user = 1;
                    user_detail_del = ptr2 ;
                }
                else{
                    ptr2 = ptr2->next ;
                }
            }
            if(del_user == 1){
                removeFromListUser(u1,user_detail_del);
                
                //iske baad traverse family ll waha se wo family dhundo jisme ye userid present ho and then family->next_mem ko user* se assign karo and fir usse iss removelist wale function me daalo

                // also this user_detail_del may be assigned as a user** since eventually we wll have to free that and if we have to bring a change in *user_detail_del we need to pass**
            }
            else{
                printf("User info dosent exist\n");
            }
        }
        else{
            
            printf("Which fam id information do u want to delete: \n");
            scanf("%d",&fam_id_del);
            fam*ptr3 = *f1;
            while((ptr3 != NULL)&&(del_fam == 0)){
                if(ptr3->fam_id == fam_id_del){
                    del_fam = 1;
                    fam_detail_del = ptr3 ;
                }
                else{
                    ptr3 = ptr3->next ;
                }
            }
            if(del_user == 1){
                removeFromListFam(f1,fam_detail_del);
                
            }
            else{
                printf("Fam info dosent exist\n");
            }
        }

    }
}

void update_delete_expense(fam** f1, expense** e1){

    int flag, found=0, found1= 0, found2 = 0, found3 = 0, exp_id_upd, exp_id_del, upd_date;
    float upd_exp_amt;
    char upd_exp_cat[CATEGORY_LEN];
    expense* ptr, *exp_upd, *exp_del;

    printf("Do you want to delete or update expense? delete=1, update=0: \n");
    scanf("%d",&flag);
    if(flag == 0){
        printf("Which expense id information do u want to update: \n");
        scanf("%d",&exp_id_upd);
        ptr = *e1 ;
        while((ptr != NULL)&&(found == 0)){
            if(ptr->expense_id == exp_id_upd){
                found = 1;
                exp_upd = ptr ;
            }
            else{
                ptr = ptr->next ;
            }
        }

        if(found == 1){
            printf("If exp cat has to be changed give different,else provide the same one: \n");
            scanf("%s",upd_exp_cat);
            printf("If u want to change the exp amt, give new exp amt else give old income: \n");
            scanf("%f",&upd_exp_amt);
            printf("If date has to be changed give different,else provide the same one: \n");
            scanf("%d",&upd_date);
            
            ptr->date = upd_date ;
            // ptr->exp_amt = upd_exp_amt ; this has been incorporated in the next loop
            strcpy(ptr->expense_cat, upd_exp_cat);

            // updating in family ll
            fam* ptr1 = *f1 ;

            while((ptr1 != NULL)&&(found1 == 0)){
                user* ptr2 = ptr1->next_user;
                while((ptr2 != NULL)&&(found1 == 0)){
                    if(ptr2->user_id == ptr->member_id){ //check  if ptr is fine or exp_upd needs to be used 
                        ptr1->fam_expense -= ptr->exp_amt ; 
                        ptr->exp_amt = upd_exp_amt ;
                        ptr1->fam_expense += ptr->exp_amt ;
                        found1 = 1;
                    }
                }
            }
            printf("Expense updated\n");
        }
        else{
            printf("Expense id not found\n");
        }
        
    }
    else{
        printf("Which expense id information do u want to delete: \n");
        scanf("%d",&exp_id_del);
        expense* ptr3 = *e1 ;
        while((ptr3 != NULL)&&(found2 == 0)){
            if(ptr3->expense_id == exp_id_del){
                found2 = 1;
                exp_del = ptr3 ;
            }
            else{
                ptr3 = ptr3->next ;
            }
        }
        if(found2 == 1){
            fam* ptr4 = *f1 ;
            while((ptr4 != NULL)&&(found3 == 0)){
                user* ptr5 = ptr4->next_user ;
                while((ptr5 != NULL)&&(found3 == 0)){
                    if(ptr5->user_id == ptr3->member_id){
                        found3 = 1;
                        ptr4->fam_expense -= ptr3->exp_amt;
                    }
                }
            }
            removeFromListExpense(e1,ptr3);
            printf("Expense deleted\n");
            //removefromListExpense
        }
        else{
            printf("Expense id not found\n");
        }

    }
}

void get_total_expense(fam** f1){
    int fam_id, flag = 0;

    printf("Enter the family id for which total expense and income is to be found: \n");
    scanf("%d",&fam_id);

    fam* ptr1 = *f1;
    while((ptr1 != NULL)&&(flag ==0)){
        if(ptr1->fam_id == fam_id){
            flag = 1;
        }
        else{
            ptr1 = ptr1->next ;
        }
    }
    printf("Total expense of family is: %f \n",ptr1->fam_expense);
    printf("Total income of family is: %f \n", ptr1->fam_income);

}

void get_individual_expense(user** u1, expense** e1){
    int id, is_true_user = 1, found = 0, found1 = 0;
    float total_exp = 0.00;
    
    while(is_true_user == 1){
        printf("Enter userID for which expense is to be calculated: \n");
        scanf("%d",&id);
        
        user* ptr = *u1 ; // check
        while((ptr != NULL)&&(!found)){
            if(ptr->user_id == id){
                found = 1;
            }
            else{
                ptr = ptr->next ;
            }
        }
        if(found == 0){
            is_true_user = 1;
        }
        else{
            is_true_user = 0;

            struct ind_cat_exp{
                float amount;
                char category[CATEGORY_LEN];
            };
            struct ind_cat_exp rec_individual[5];
            const char cats[5][CATEGORY_LEN] = {"RENT","UTILITY","GROCERY","STATIONARY","LEISURE"};
            for(int x=0;x<5;x++){
                rec_individual[x].amount = 0.00;
                strcpy(rec_individual[x].category,cats[x]);
            }

            expense* ptr1 = *e1;
            expense* ptr1_found ;
            while((ptr1 != NULL)&&(found1 == 0)){
                if(ptr1->member_id == id){
                    ptr1_found = ptr1 ;
                    while((ptr1 != NULL)&&(ptr1->member_id == id)){
                        if(strcmp(ptr1->expense_cat,"RENT") == 0){
                            rec_individual[0].amount+=ptr1->exp_amt;
                        }
                        else if(strcmp(ptr1->expense_cat,"UTILITY")==0){
                            rec_individual[1].amount+=ptr1->exp_amt;
                        }
                        else if(strcmp(ptr1->expense_cat,"GROCERY")==0){
                            rec_individual[2].amount+=ptr1->exp_amt;
                        }
                        else if(strcmp(ptr1->expense_cat,"STATIONARY")==0){
                            rec_individual[3].amount+=ptr1->exp_amt;
                        }
                        else if(strcmp(ptr1->expense_cat,"LEISURE")==0){
                            rec_individual[4].amount+=ptr1->exp_amt;
                        }
                        else{
                            printf("Category dosent exist\n");
                        }
                        total_exp += ptr1->exp_amt ;
                        ptr1 = ptr1->next;
                    }
                    found1 = 1;
                }
                else{
                    ptr1 = ptr1->next ;
                }
            }
            printf("Total expense for userId %d is %f\n",id,total_exp);
           
            //sort the array formed above using modified bubble sort
            int sort=0;
            struct ind_cat_exp temp;

            for(int k=0;k<4 && sort==0;k++){
                sort=1;
                for(int j=0;j<4-k;j++){
                    if(rec_individual[j].amount<rec_individual[j+1].amount){
                        temp=rec_individual[j];
                        rec_individual[j]=rec_individual[j+1];
                        rec_individual[j+1]=temp;
                        sort=0;
                    }
                }
            }
            for(int l=0;l<5;l++){
                printf("Category: %s\n",rec_individual[l].category);
                printf("Expense amount is %f \n",rec_individual[l].amount);
            } 
        }
    }
}

void get_categorical_expense(fam** f1, user** u1, expense** e1){

    int fam_id, found_fam = 0;
    float total_exp = 0.00;
    char cat[CATEGORY_LEN];
    fam* fam_detail_req ;

    printf("Enter category for which expense is to be found\n");
    scanf("%s",cat);

    printf("Which fam id information do u want to retrieve: \n");
    scanf("%d",&fam_id);
    fam* ptr = *f1;
    while((ptr != NULL)&&(found_fam == 0)){
        if(ptr->fam_id == fam_id){
            found_fam = 1;
            fam_detail_req = ptr ;
        }
        else{
            ptr = ptr->next ;
        }
    }
    if(found_fam == 1){

        struct specific_cat_fam_exp{
            int user_ka_id;
            float user_ka_exp;
        };
        struct specific_cat_fam_exp rec_cat_family[4];
        struct specific_cat_fam_exp temp;
        for(int i=0;i<4;i++){
            rec_cat_family[i].user_ka_exp=0.00;
            rec_cat_family[i].user_ka_id=0;
        } // intialization done


        int i = 0;
        int len_rec_cat_family = 0;
        user* ptr1 = ptr->next_user ;
        while(ptr1 != NULL){
            expense* ptr2 = *e1 ;
            while(ptr2 != NULL){
                if(ptr1->user_id == ptr2->member_id){
                    float ind_exp_amt = 0.00;
                    while((ptr2 != NULL)&&(ptr1->user_id == ptr2->member_id)){
                        if(strcmp(ptr2->expense_cat , cat) == 0){
                            ind_exp_amt += ptr2->exp_amt;
                            total_exp += ptr2->exp_amt;
                            ptr2 = ptr2->next ;
                        }
                        else{
                            ptr2 = ptr2->next;
                        }
                    }
                    rec_cat_family[i].user_ka_exp = ind_exp_amt;
                    rec_cat_family[i].user_ka_id = ptr1->user_id ;
                    len_rec_cat_family += 1;
                    i++;
                }
                else{
                    ptr2 = ptr2->next ;
                }
            }
            ptr1 = ptr1->next ;
        }
        printf("Total  expense for family in this category is: %f\n",total_exp);

        int sort= 0;
        for(int k=0;k<len_rec_cat_family-1 && sort==0;k++){
            sort=1;
            for(int j=0;j<len_rec_cat_family-k-1;j++){
                if(rec_cat_family[j].user_ka_exp<rec_cat_family[j+1].user_ka_exp){
                    temp=rec_cat_family[j];
                    rec_cat_family[j]=rec_cat_family[j+1];
                    rec_cat_family[j+1]=temp;
                    sort=0;
                }
            }
                
        }

        for(int l=0;l<len_rec_cat_family;l++){
            printf("User id: %d \n",rec_cat_family[l].user_ka_id);
            printf("Expense amount is %f \n",rec_cat_family[l].user_ka_exp);
        }
    }
    else{
        printf("FamID not found\n");
    }
}

void get_highest_expense_day(fam**f1, expense** e1, user ** u1){
    int fam_id, found_fam = 0;
    float date_arr[10];
    for(int i = 0 ;i<10; i++){
        date_arr[i] = 0.00;
    }

    printf("For which family id do you want to calculate the highest expense day: \n");
    scanf("%d",&fam_id);
    fam* ptr = *f1;
    while((ptr != NULL)&&(found_fam == 0)){
        if(ptr->fam_id == fam_id){
            found_fam = 1;
        }
        else{
            ptr = ptr->next ;
        }
    }
    if(found_fam == 1){
        user* ptr1 = ptr->next_user ;
        while(ptr1 != NULL){
            expense* ptr2 = *e1;
            while(ptr2 != NULL){
                if(ptr1->user_id == ptr2->member_id){
                    date_arr[ptr2->date - 1] += ptr2->exp_amt;
                    ptr2 = ptr2->next ;
                }
                else{
                    ptr2 = ptr2->next ;
                }
            }
            ptr1 = ptr1->next ;
        }
        float max=date_arr[0];
        int loc=0;
        for(int m=0;m<10;m++){
            if(date_arr[m]>max){
                max=date_arr[m];
                loc=m;
            }
        }

        printf("Date at which maximum family expense incurred is %d \n",loc+1);
        printf("Expense amount is %f \n",max);
    }
    else{
        printf("Family not found \n");
    }
}

int main(){
    user* u1 = NULL;
    int cj ;
    expense* e1 = NULL;
    fam* f1 = NULL;

    int fam_id = 0 ;

    int exit_loop = 0;
    while(!exit_loop){
        int menu_code, status_code ;
        printf("\tExpense Tracking System\n");
        printf("\t \tMenu\n1. Add User\n2. Add Expense\n3. Update or delete individual family details\n4. Update or delete expense\n5. Get total expense for a family\n6. Get individual expense of an user\n7. Get categorical expense of a family\n8. Get the highest expense day of a family\n9. Exit\n");
        printf("Enter number between 1 and 10\n");
        scanf("%d",&menu_code);
        if((menu_code < 1) || (menu_code > 10)){
            printf("Invalid input\n");
        }
        else{
            switch(menu_code){
                case 1:
                addUser(&u1,&cj,&fam_id,&f1);
                break;
                case 2:
                addExpense(&e1,&u1,&f1);
                break;
                case 3:
                update_individual_fam_details(&u1,&f1);
                break;
                case 4:
                update_delete_expense(&f1, &e1);
                case 5:
                get_total_expense(&f1);
                break;
                case 6:
                get_individual_expense(&u1,&e1);
                break;
                case 7:
                get_categorical_expense(&f1,&u1,&e1);
                break;
                case 8:
                get_highest_expense_day(&f1,&e1,&u1);
                case 9:
                exit_loop = 1;
                break;
                default:
                break;

            }
        }
        printf("If you want to continue enter 1 else 0 \n");
        scanf("%d",&status_code);
        if(status_code == 1){
            exit_loop = 0;
        }
        else{
            exit_loop = 1 ;
        }
    }

    return 0 ;
     
    
}