/* this file uses function components */
module ReasonReact = Hooks.ReasonReact;

module Just = {
  let component =
    (. props: {. "initialValue": int}) => {
      let (count, setCount) =
        Hooks.(unwrap(useState(wrap(props##initialValue))));
      let (show, setShown) = Hooks.(unwrap(useState(true)));
      let (_name, _setName) =
        Random.bool() ?
          Hooks.(unwrap(Hooks.useState("Harry"))) : ("", (. _) => ());

      <div>
        {
          show ?
            <h1> {ReasonReact.string(string_of_int(count))} </h1> :
            ReasonReact.null
        }
        <button onClick={_evt => setCount(. count + 1)}>
          {ReasonReact.string("Count Up To The Moon")}
        </button>
        <button onClick={_evt => setShown(. !show)}>
          {ReasonReact.string(show ? "Hide" : "Show")}
        </button>
      </div>;
    };
  component->Hooks.setName("Just");

  let make = (~initialValue, _children) =>
    Hooks.createElement(~component, ~props={"initialValue": initialValue});
};

ReactDOMRe.renderToElementWithId(<Just initialValue=10 />, "root");