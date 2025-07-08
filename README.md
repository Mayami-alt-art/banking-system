# banking-system
# Banking System - Secure Login

## Overview
This C++ program implements a secure banking system with separate login interfaces for administrators and users. The system provides functionality for user registration, deposits, withdrawals, balance checking, and password management.

## Features

### Administrator Functions
- **Login**: Secure admin authentication
- **User Registration**: Register new clients with username and password
- **Deposit Funds**: Add money to a user's account
- **Password Reset**: Change admin password

### User Functions
- **Login**: Secure user authentication with masked password input
- **Withdraw Cash**: Withdraw money from account (with balance check)
- **Check Balance**: View current account balance
- **Change Password**: Update user password

## Security Features
- Password masking during input
- Secure credential storage in text files
- Username uniqueness validation
- Separate authentication for admin and users

## File Structure
- `admin.txt`: Stores administrator credentials
- `usersDB.txt`: Stores all user accounts with passwords and balances
- `temp.txt`: Temporary file used during account updates

## How to Use
1. Compile the program using a C++ compiler
2. Run the executable
3. Choose between:
   - Administrator login (default credentials stored in admin.txt)
   - User login (must be registered first)
   - Exit the system

## Requirements
- C++ compiler (supporting C++11 or later)
- Windows system (for `conio.h` functionality)
- Basic file I/O permissions

## Notes
- For first-time use, ensure `admin.txt` exists with proper admin credentials
- All user data is stored in plaintext - consider additional security measures for production use
- The program uses temporary files for atomic updates to user accounts

## Limitations
- No encryption for stored passwords
- Basic file-based storage (not suitable for large-scale systems)
- Windows-specific password masking (`conio.h`)
