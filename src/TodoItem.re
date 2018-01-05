type item = {
  title: string,
  completed: bool,
  id: int
};
let str = ReasonReact.stringToElement;
let component = ReasonReact.statelessComponent("TodoItem");
let make = (~item, ~onToggle, _children) => {
  ...component,
  render: (_self) =>
    <div className="item">
      <input
        _type="checkbox"
        onChange=((_evt) => onToggle())
        checked=(Js.Boolean.to_js_boolean(item.completed))
      />
      (str(item.title))
    </div>
};