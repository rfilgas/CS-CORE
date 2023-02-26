#include "account_manager.h"

int account_manager::add_account(account &input_account, string &UID) // access level 1: return UID.
{
    //add an acount to the map of accounts
    account new_account;
   
    input_account.copy(new_account);
  
    //add new account to map
    accounts[UID] = new_account;
    int ret_ID = std::stoi(UID);
    return ret_ID;
}
int account_manager::update_account(account &to_add, string &UID)  //lvl 1
{
    //update an existing account based on ID
    map<string,account>::iterator it;       //iterator to find matching ID
    it = accounts.find(UID);
    if(it != accounts.end())
    {
        account edit_account;
        edit_account.update(to_add);
        accounts[UID] = edit_account;       //replace old info with new account info
        return 1;
    }

    return -1;
}

int account_manager::remove_account(string &UID) //lvl 1
{
    //remove an account from the map based on ID
    map<string,account>::iterator it;       //iterator to find matching ID
    it = accounts.find(UID);

    if(it != accounts.end())
    {
        accounts.erase(it);         //deletes matching account by ID
        return 1;
    }

    return -1;
}

int account_manager::display_account(string &UID)
{
    //display a single account by matching ID
    map<string,account>::iterator it;       //iterator to find matching ID
    it = accounts.find(UID);

    if(it != accounts.end())
    {
        it->second.display();
        return 1;
    }

    return -1;
}

int account_manager::display_mems(void) //lvl 1
{
    //display all members
    return -1;
}

int account_manager::display_provs(void) //lvl 1
{


    return -1;
}

