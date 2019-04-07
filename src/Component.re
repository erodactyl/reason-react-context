type state = {value: int};

type action =
  | Increment
  | Decrement;

let component = ReasonReact.reducerComponent("Component");

let make = _children => {
  ...component,
  initialState: () => {value: 0},
  reducer: (action, {value}) => {
    switch (action) {
    | Increment => ReasonReact.Update({value: value + 1})
    | Decrement => ReasonReact.Update({value: value - 1})
    };
  },
  render: ({send, state: {value}}) => {
    <AppContext.Context.Provider value>
      ...<div>
           <AppContext.Context.Consumer>
             ...{value =>
               <div> {ReasonReact.string(string_of_int(value))} </div>
             }
           </AppContext.Context.Consumer>
           <button onClick={_ => send(Increment)}>
             {ReasonReact.string("Increment")}
           </button>
           <button onClick={_ => send(Decrement)}>
             {ReasonReact.string("Decrement")}
           </button>
         </div>
    </AppContext.Context.Provider>;
  },
};