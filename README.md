# reason-react-context

## Run Project

```sh
npm install
npm start
# in another tab
npm run webpack
```

After you see the webpack compilation succeed (the `npm run webpack` step), open up `build/index.html` (**no server needed!**). Then modify whichever `.re` file in `src` and refresh the page to see the changes.

**For more elaborate ReasonReact examples**, please see https://github.com/reasonml-community/reason-react-example

## Run Project with Server

To run with the webpack development server run `npm run server` and view in the browser at http://localhost:8000. Running in this environment provides hot reloading and support for routing; just edit and save the file and the browser will automatically refresh.

Note that any hot reload on a route will fall back to the root (`/`), so `ReasonReact.Router.dangerouslyGetInitialUrl` will likely be needed alongside the `ReasonReact.Router.watchUrl` logic to handle routing correctly on hot reload refreshes or simply opening the app at a URL that is not the root.

To use a port other than 8000 set the `PORT` environment variable (`PORT=8080 npm run server`).

## Functors

Each React component is a module in ReasonReact. Unfortunately, modules can't be simply pass to or returned from functions, as they are on another layer of the language. You can read more about this [here](https://reasonml.github.io/docs/en/module#docsNav)

So, to bypass this, we will need to use a Functor, which is a language construct, similar to functions, that taked a module and returns a module. Unlike functions, there is no type inference in functor argument type, so we have to manually add it ourselves. That's why we have the module type in the ContextConfig in ReasonContext.re file.

## ReasonContext

Inside our Context module we define a mutable variable "state", and modules Provider and Consumer, which are both React components. The state variable is where we keep the value of the context, and we want all components dependednt on it to rerender when we change the state. So we add a subscribers array, subscibe function that returns the unsubscribe function, and a setState function to the module, which sets the new state and iterates over the subscribers, signaling them that the state changed and they need to rerender.

We call this setState function every time in the didUpdate record field of the Provider make function, and we subscribe in the didMount record field in the Consumer make function. These are the usual ReasonReact lifecycle, you can read more about them [here](https://reasonml.github.io/reason-react/docs/en/lifecycles.html).

### onUnmount

It's important not to forget to unsubscribe when the comopnent unmounts. The onUnmount function destructured in the didMount arguments is simply a subscribtion helper for the willUnmount record field to reduce boilerplate code, you can read more about it [here](https://reasonml.github.io/reason-react/docs/en/subscriptions-helper#docsNav).

## Usage

We use this context in the same way as we would use the React context. A functional difference is that we haven't implemented the logic to nest Providers and take the values of the last one. Syntactically, we have to use ...(children) to make the types match, you can read more about that [here](https://reasonml.github.io/reason-react/docs/en/children#children-spread).
