
# GenPass
**GenPass** is a lightweight and efficient command-line tool for generating secure passwords. Whether you need a simple password or a more complex one with custom symbols, GenPass has you covered.

## Features
1. **Simplicity:** Easy-to-use interface with minimal input required.
2. **Speed:** Generates passwords instantly, making it perfect for quick tasks.
3. **Customizable Length:** Specify the exact length of the password you need.
4. **Symbol Selection:** Choose from predefined sets of characters, including letters, numbers, and symbols, or define your own custom set.

## Usage
- **Basic password:** Generate a password with random letters and numbers.
- **Advanced password:** Generate a password that includes letters, numbers, and special symbols.
- **Custom password:** Define your own set of characters to be included in the password.

## Example

```console
Enter the length of the password (0 to exit): 12
Choose a type of password:
1. Random letters and numbers
2. Random letters, numbers, and symbols
3. Custom symbols only
4. Pronounceable password
5. View password history
6. Clear password history
Enter your choice: 2
Do you want to exclude similar characters like 'O', '0', 'l', '1', etc.? (y/n): y
Generated Password: 'c_ZRP!$cm37
Password Strength: [######] Strong
Do you want to generate a new password? (y/n): n
```

## To-Do
- [X] **Add possibility to choose what symbols can be included:** If the user input is "qyuioplkjhgvbnmZCSA712", the password will only include these symbols.
- [X] **Add option to exclude similar characters:** Exclude easily confused characters like 'O' and '0', 'l' and '1', etc.
- [X] **Add option for pronounceable passwords:** Generate passwords that are easier to remember and pronounce.
- [X] **Add password strength indicator:** Provide feedback on the strength of the generated password.
- [ ] **Implement clipboard copy feature:** Automatically copy the generated password to the clipboard.
- [X] **Add user prompts for invalid inputs:** Improve input validation with clear prompts and suggestions.
- [ ] **Create a GUI version:** Develop a simple graphical user interface for those who prefer not to use the command line.
- [ ] **Add configuration file support:** Allow users to save and reuse their preferred settings.
- [ ] **Add multi-language support:** Enable the tool to support multiple languages for a broader user base.
- [X] **Implement password history:** Keep a log of previously generated passwords with an option to review or delete.

## License

This project is licensed under the MIT License. See the [LICENSE](./LICENSE) file for details.