class PubSub:
    def __init__(self):
        self._subscribers = {}

    def subscribe(self, event_type, fn):
        """Subscribers register to listen to specific events."""
        if not event_type in self._subscribers:
            self._subscribers[event_type] = []
        self._subscribers[event_type].append(fn)

    def unsubscribe(self, event_type, fn):
        """Subscribers can unregister from specific events."""
        if event_type in self._subscribers:
            self._subscribers[event_type].remove(fn)

    def publish(self, event_type, data):
        """Publishers can trigger events and pass data."""
        if event_type in self._subscribers:
            for subscriber in self._subscribers[event_type]:
                subscriber(data)


# Usage
pubsub = PubSub()

# Define a subscriber
def print_data(data):
    print(f"Received data: {data}")

# Subscribe the subscriber to an event
pubsub.subscribe('EVENT_TYPE', print_data)

# Publish an event
pubsub.publish('EVENT_TYPE', "Hello, World!")

# Unsubscribe the subscriber from the event
pubsub.unsubscribe('EVENT_TYPE', print_data)
