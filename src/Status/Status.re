open ReasonUrql;
type state = string;

module ChangeUserStatus = [%graphql
 {|
   mutation changeUserStatus($message: String!) {
     changeUserStatus(input: {
   message: $message,
 }) {
       status{
           message
       }
     }
   }
 |}
];


[@react.component]
let make = _ => {

let (state, setState) = React.useState(() => "test");

 let handleChange = e => {
 setState(e->ReactEvent.Form.target##value);
};

let (_, executeMutation) = Hooks.useDynamicMutation(ChangeUserStatus.definition);

 let handleSubmit = e => {
 e->ReactEvent.Form.preventDefault;
 executeMutation(
         ~message=state,
         ()
       ) |> ignore
};

 <div>
   <form onSubmit={handleSubmit}>
     <label htmlFor="status">"Status: "->React.string</label>
     <input id="status" value={state} name="status" onChange={handleChange} />
     <input type_="submit" value="Submit"/> 
   </form>
 </div>;
};

/*
A faire form avec input qui modifie le state, mettre dans le state les autres champs du status avec useeffect, btn click usemutation
*/