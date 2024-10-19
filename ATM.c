#include<stdio.h>
#include<string.h>
#define Max_account 2
#define Max_history 10

struct Account
{
    char account_number[20];
    char password[8];
    double balance;
};

struct ATM
{
    struct Account accounts[Max_account];
    char transaction_history[Max_history][50];
    int transaction_count;
}atm;

void initialize_account(struct ATM *atm)
{
    strcpy(atm -> accounts[0].account_number, "12345");
    strcpy(atm -> accounts[0].password, "abc");
    atm -> accounts[0].balance = 10000;

    strcpy(atm -> accounts[1].account_number, "67890");
    strcpy(atm -> accounts[1].password, "xyz");
    atm -> accounts[1].balance = 23000;
}

int login(struct ATM *atm, char *acc_num, char *pass)
{
    for(int i = 0; i < 2; i++)
    {
        if(strcmp(atm -> accounts[i].account_number, acc_num) == 0)
        {
            if(strcmp(atm -> accounts[i].password, pass) == 0)
            {
            printf("Login Successful!\n");
            return i;
            }
        }
    }
    printf("Invalid Credentials!");
    return -1;
}

void check_balance(struct ATM *atm, int acc_ind)
{
    printf("Your Balance is %.2lf\n", atm -> accounts[acc_ind].balance);
    if(atm -> transaction_count < Max_history)
    {
        snprintf(atm -> transaction_history[atm -> transaction_count], 50, "Checked Balance: %.2lf", atm -> accounts[acc_ind].balance);
        atm -> transaction_count++;
    }
}

void deposit_money(struct ATM *atm, double amt, int acc_index)
{
    if(amt > 0)
    {
        printf("Amount %.2lf has been deposited!\n", amt);
        atm -> accounts[acc_index].balance += amt;

        printf("Your Balance: %.2lf\n", atm -> accounts[acc_index].balance);

        if(atm -> transaction_count < Max_history)
        {
            snprintf(atm -> transaction_history[atm -> transaction_count], 50, "Deposited money: %.2lf\n", amt);
            atm -> transaction_count++;
        }
    }
    else
        printf("Invalid amount!\n");
}

void withdraw_money(struct ATM *atm, double amt, int acc_index)
{
    if(amt > 0 && atm -> accounts[acc_index].balance >= amt)
    {
        printf("Amount %.2lf has been withdrawn!\n", amt);
        atm -> accounts[acc_index].balance -= amt;

        printf("Your Balance: %.2lf\n", atm -> accounts[acc_index].balance);


        if(atm -> transaction_count < Max_history)
        {
            snprintf(atm -> transaction_history[atm -> transaction_count], 50, "Withdrew money: %.2lf\n", amt);
            atm -> transaction_count++;
        }
    }
    else
        printf("Invalid amount!\n");
}

void transaction_history(struct ATM *atm)
{
    printf("Transaction history: \n");
    for(int i = 0; i < atm -> transaction_count; i++)
        printf("%s\n", atm -> transaction_history[i]);
}

int main()
{
    atm.transaction_count = 0;
    initialize_account(&atm);

    char acc_num[20], pass[20];
    int acc_index, option;
    double amount;
    int exit = 0;

    printf("Welcome to our ATM!!!\n");
    printf("Enter your account number: "); 
    scanf("%s", acc_num);
    printf("Enter your password: ");
    scanf("%s", pass);

    acc_index = login(&atm, acc_num, pass);

    if(acc_index != -1)
    {
        while(!exit)
        {
            printf("\nATM Menu:\n");
            printf("1. Check Balance\n");
            printf("2. Deposit Money\n");
            printf("3. Withdraw Money\n");
            printf("4. View Transaction History\n");
            printf("5. Exit\n");
            printf("Choose an option: ");
            scanf("%d", &option);

            switch(option)
            {
                case 1:
                    check_balance(&atm, acc_index);
                    break;

                case 2:
                    printf("Enter amount to be deposited: ");
                    scanf("%lf", &amount);
                    deposit_money(&atm, amount, acc_index);
                    break;

                case 3:
                    printf("Enter amount to be withdrawn: ");
                    scanf("%lf", &amount);
                    withdraw_money(&atm, amount, acc_index);
                    break;

                case 4:
                    transaction_history(&atm);
                    break;
                case 5:
                    exit = 1;
                    break;
                default:
                    printf("Please enter valid option!\n");
            }
        }
        printf("Thank you for using our ATM!!!");
    }
}