import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;

class ATM 
{
    HashMap<String, String> account_details = new HashMap<>();
    HashMap<String, Double> balance_details = new HashMap<>();
    ArrayList<String> transaction_history = new ArrayList<>();
    Scanner sc = new Scanner(System.in);
    
    public void initialize_accounts() 
    {
        account_details.put("12345", "xyz");
        balance_details.put("12345", 15000.0);
        
        account_details.put("67890", "abc");
        balance_details.put("67890", 23000.0);
    }
    
    public boolean login_account(String account_number, String password) 
    {
        if(account_details.containsKey(account_number) && account_details.get(account_number).equals(password)) 
        {
            System.out.println("Login successful!");
            return true;
        } 
        else 
        {
            System.out.println("Invalid account number or password!");
            return false;
        }
    }
    
    public void check_balance(String account_number) 
    {
        double balance = balance_details.get(account_number);
        System.out.println("Your current balance is: " + balance);
        transaction_history.add("Checked balance: " + balance);
    }
    
    public void deposit(String account_number, double amount) {
        if (amount > 0) {
            double current_balance = balance_details.get(account_number);
            balance_details.put(account_number, current_balance + amount);
            System.out.println("Deposit successful! \n New balance: " + balance_details.get(account_number));
            transaction_history.add("Deposited: " + amount);
        } 
        else 
        {
            System.out.println("Invalid deposit amount!");
        }
    }
    
    public void withdraw(String account_number, double amount) {
        double current_balance = balance_details.get(account_number);
        if (amount > 0 && current_balance >= amount) {
            balance_details.put(account_number, current_balance - amount);
            System.out.println("Withdrawal successful! \n New balance: " + balance_details.get(account_number));
            transaction_history.add("Withdrew: " + amount);
        } 
        else 
        {
            System.out.println("Insufficient balance or invalid amount!");
        }
    }
    
    public void view_transaction_history() 
    {
        System.out.println("Transaction history:");
        for (String transaction : transaction_history) {
            System.out.println(transaction);
        }
    }

    public static void main(String[] args) {
        ATM atm = new ATM();
        atm.initialize_accounts(); 
        Scanner sc = new Scanner(System.in);
        
        System.out.println("Welcome to the ATM!!!");
        System.out.print("Enter account number: ");
        String account_number = sc.nextLine();
        
        System.out.print("Enter password: ");
        String password = sc.nextLine();
        
        if (atm.login_account(account_number, password)) {
            boolean exit = false;
            while(!exit) 
            {
                System.out.println("\nATM Menu:");
                System.out.println("1. Check Balance");
                System.out.println("2. Deposit Money");
                System.out.println("3. Withdraw Money");
                System.out.println("4. View Transaction History");
                System.out.println("5. Exit");
                
                System.out.print("Choose an option: ");
                int option = sc.nextInt();
                
                switch(option) 
                {
                    case 1:
                        atm.check_balance(account_number);
                        break;
                    case 2:
                        System.out.print("Enter amount to deposit: ");
                        double deposit_amount = sc.nextDouble();
                        atm.deposit(account_number, deposit_amount);
                        break;
                    case 3:
                        System.out.print("Enter amount to withdraw: ");
                        double withdraw_amount = sc.nextDouble();
                        atm.withdraw(account_number, withdraw_amount);
                        break;
                    case 4:
                        atm.view_transaction_history();
                        break;
                    case 5:
                        exit = true;
                        System.out.println("Thank you for using our ATM!!!");
                        break;
                    default:
                        System.out.println("Invalid option, Please try again!");
                        break;
                }
            }
        }
    }
}