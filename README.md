# Simple Text Editor in C

This is a simple text editor implemented in C, utilizing two linked lists as a stack data structure to manage the text data. The editor supports basic operations such as undo, redo, read, insert, delete, and move cursor.

## Features

- **Undo**: Reverts the most recent change made to the text.
- **Redo**: Reapplies the most recent undone change.
- **Read**: Displays the current content of the text.
- **Insert**: Inserts text at the current cursor position.
- **Delete**: Deletes text at the current cursor position.
- **Move Cursor**: Moves the cursor to a specified position in the text.

## Implementation Details

- **Linked Lists**: Two linked lists are used to represent the text data. One list holds the text before the current cursor position, and the other holds the text after the current cursor position. This setup allows for efficient insertion, deletion, and movement operations.
- **Stack Data Structure**: The linked lists are used as stacks to support undo and redo operations. Whenever a change is made to the text, it is pushed onto the undo stack. Undoing a change pops it from the undo stack and pushes it onto the redo stack. Redoing a change pops it from the redo stack and pushes it onto the undo stack.
- **Cursor Management**: The cursor position is tracked separately from the text data. This allows for easy movement of the cursor without modifying the underlying text.

## Usage

To compile the text editor, run:

```bash
gcc text_editor.c -o text_editor
```

To run the text editor, execute the compiled binary:

```bash
./text_editor
```

Once the editor is running, you can use the following commands:

- `u`: Undo the most recent change.
- `r`: Redo the most recently undone change.
- `d`: Display the current content of the text.
- `i`: Insert text at the current cursor position.
- `del`: Delete text at the current cursor position.
- `m`: Move the cursor to a specified position.

## Contributing

Contributions are welcome! If you find any issues or have suggestions for improvements, please feel free to open an issue or submit a pull request.
