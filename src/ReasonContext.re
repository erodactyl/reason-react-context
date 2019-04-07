module type ContextConfig = {
  type contextType;
  let defaultValue: contextType;
};

module CreateContext = (Config: ContextConfig) => {
  type subscriber = unit => unit;
  // type consumerState = {updater: bool};
  type consumerAction =
    | Update;

  let state = ref(Config.defaultValue);
  let subscribers: ref(list(subscriber)) = ref([]);
  let subscribe = (cb: subscriber) => {
    subscribers := [cb, ...subscribers^];
    () => {
      subscribers := List.filter(c => c !== cb, subscribers^);
    };
  };

  let setState = value => {
    state := value;
    List.iter(sub => sub(), subscribers^);
  };

  module Provider = {
    let component = ReasonReact.statelessComponent("Provider");
    let make = (~value, children) => {
      ...component,
      didMount: _ => {
        setState(value);
      },
      didUpdate: _ => {
        setState(value);
      },
      render: _ => children,
    };
  };

  module Consumer = {
    let component = ReasonReact.reducerComponent("Consumer");
    let make = children => {
      ...component,
      initialState: () => true,
      didMount: ({send, onUnmount}) => {
        let unsub = subscribe(() => send(Update));
        onUnmount(() => unsub());
      },
      reducer: (_, state) => ReasonReact.Update(!state),
      render: _ => children(state^),
    };
  };
};