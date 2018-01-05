[%bs.raw {|require('./app.css')|}];

[@bs.module] external logo : string = "./logo.svg";

type item = TodoItem.item;

type state = {
  items: list(item)
};

type action =
  | AddItem(string)
  | ToggleItem(int);

let str = ReasonReact.stringToElement;
let lastId = ref(0);
let component = ReasonReact.reducerComponent("App");
let newItem = (text) : item => {
  lastId := lastId^ + 1;
  {title: text, completed: true, id: lastId^}
};
let iterate = (component, items) => List.map(component, items) |> Array.of_list |> ReasonReact.arrayToElement;

let make = (_children) => {
  ...component,
  initialState: () => {
    items: [
      {title: "Write some things to do", completed: false, id: 0}
    ]
  },
  reducer: (action, {items}) =>
    switch action {
    | AddItem(text) => ReasonReact.Update({items: [newItem(text), ...items]})
    | ToggleItem(id) =>
      let items = List.map((item : item) =>
        item.id === id
          ? {...item, completed: !item.completed}
          : item
      , items);
      ReasonReact.Update({items: items})
    },
  render: ({state: {items}, reduce}) => {
    let numItems = List.length(items);
    <div className="app">
      <div className="title"> (str("What to do")) 
        <Input onSubmit=(reduce((text) => AddItem(text))) />
      </div>
      <div className="items">
        (iterate((item : item) => <TodoItem item onToggle=(reduce(() => ToggleItem(item.id))) key=(string_of_int(item.id)) />, items))
      </div>
      <div className="footer">
        (str(string_of_int(numItems) ++ " items"))
      </div>
    </div>
  }
};
