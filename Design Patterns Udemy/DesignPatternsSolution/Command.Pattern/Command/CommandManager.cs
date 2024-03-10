namespace Command.Pattern.Command;
public class CommandManager
{
    Stack<ICommand> commands = new();

    public void Invoke(ICommand command)
    {
        if (command.CanExecute())
        {
            command.Execute(); 
            commands.Push(command);
        }
    }

    public void Undo()
    {
        while (commands.Count > 0)
        {
            var command = commands.Pop();
            if (command.IsUndoAllowed)
            {
                command.Undo();
            }
            else
            {
                break; 
            }
        }
    }
}
