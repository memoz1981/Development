namespace Command.Pattern.Command;
public interface ICommand
{
    void Execute();
    bool CanExecute();
    void Undo();
    bool IsUndoAllowed { get; }
}
